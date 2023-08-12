#include <sodium.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <thread>
#include <mutex>
#include "msd/channel.hpp"

#include "network-manager.h"
#include "connection-factory.h"
#include "connection.h"
#include "messages/message.h"
#include "messages/stream-in/server/public-key.h"
#include "messages/internal/event-error.h"
#include "utility/data.h"

using namespace model;

namespace {
  void LaunchCallbackHandler(std::shared_ptr<event_base> connection_base) {
    event_base_loop(connection_base.get(), EVLOOP_NO_EXIT_ON_EMPTY);
  }

  void LaunchChannelHandler(std::mutex &connections_mutex, msd::channel<std::shared_ptr<Data>> &in_chann, std::unordered_map<int, std::shared_ptr<Connection>> &connections) {
    // read incoming channel data from connection callbacks
    for (const std::shared_ptr<Data> data: in_chann) { // blocks forever waiting for channel items
      /*printf("<data read from in_chann: %s>", data);

      std::unique_ptr<Message> message;
      if (data.contains("plaintext") && DeserializeStreamIn(message.get(), data.at("plaintext")) != 0) {
        // failed to deserialize data
        continue;
        
      } else if (data.contains("internal") && DeserializeInternal(message.get(), data.at("internal")) != 0) {
        // failed to deserialize data
        continue;
        
      } else {
        // invalid data
        continue;
      }

      int sockfd = data.at("sockfd");

      connections_mutex.lock();

      if (message->GetType() == server_stream_in::kPublicKey) {
        std::unique_ptr<server_stream_in::PublicKey> recv_pk(dynamic_cast<server_stream_in::PublicKey*>(message.get()));
        const unsigned char* recv_pk_ptr = reinterpret_cast<const unsigned char*>(recv_pk->GetKey().c_str());

        auto conn = connections.at(sockfd);
        
        connections_mutex.unlock();
        
        if (conn->EstablishSecureConnection(recv_pk_ptr) != 0) {
          // panic! failed to create secure connection
          continue;
        }

        printf("<secure sockfd connection established: %d>", sockfd);

      } else if (message->GetType() == internal::kEventError) {
        std::unique_ptr<internal::EventError> err(dynamic_cast<internal::EventError*>(message.get()));

        printf("<EventError msg: %s>", err->GetMsg());

        connections.erase(sockfd);
      
        connections_mutex.unlock();
      } else {
        connections_mutex.unlock();
      }*/
    }
  }
} // namespace


NetworkManager::NetworkManager() {
  connection_base.reset(event_base_new(),
    [](event_base *b){
      event_base_loopexit(b, NULL);
      event_base_free(b);
    }
  );
}

NetworkManager::~NetworkManager() {
  connections.clear();
}

void NetworkManager::Launch() {
  // todo - might be good as a coroutine

  // start event base loop for connection callbacks
  std::jthread callback_thread(
    LaunchCallbackHandler,
    this->connection_base
  );

  // start channel loop for reading incoming data from connection callbacks
  std::jthread channel_handler(
    LaunchChannelHandler,
    std::ref(this->connections_mutex),
    std::ref(this->in_chann),
    std::ref(this->connections)
  );
}

int NetworkManager::ConnectToServiceServer() {
  // fake ip address and port for testing
  const std::string ip_address = "1234";
  const std::string port = "1234";

  if (sodium_init() < 0) {
    /* panic! library wont initilise */
    return -1;
  }

  auto service = model_connection_factory::GetConnection(connection_base, std::ref(in_chann), ip_address, port);
  
  int sockfd = service->CreateConnection();

  // create a TCP connection
  if (sockfd == -1) {
    // TCP connection failed
    return sockfd;
  }
  
  // store connection in map
  std::pair<int, std::shared_ptr<Connection>> connection_pair(sockfd, service);

  connections_mutex.lock();
  connections.insert(connection_pair);
  connections_mutex.unlock();

  // request for secure connection with service server
  if(InitiateSecureConnection(sockfd) != 0) {
    // failed to initiate secure connection with service server
    return -1;
  }

  return 0;
}

int NetworkManager::InitiateSecureConnection(const int &sockfd) {
  connections_mutex.lock();

  if (!connections.contains(sockfd)) {
    return -1;
  }

  auto conn = connections.at(sockfd);

  connections_mutex.unlock();

  // send public key to sockfd connection
  if (conn->SendPublicKey() != 0) {
    // panic! failed to send public key to scokfd connection
    return -1;
  }

  return 0;
}

int NetworkManager::SendMessage(const int &id, std::string &data) {
  connections_mutex.lock();

  if (!connections.contains(id)) {
    return -1;
  }

  std::unique_ptr<Message> message;
  if (DeserializeStreamOut(message.get(), data) != 0) {
    return -1;
  }

  int sent_bytes = connections.at(id)->SendMessage(message.get());

  connections_mutex.unlock();

  return sent_bytes;
}