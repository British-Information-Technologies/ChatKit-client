#include <sodium.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <mutex>
#include <thread>
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
  void LaunchConnectionBaseHandler(std::shared_ptr<event_base> connection_base) {
    printf("[NetworkManager]: connection base launched\n");
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
  connection_base_thread->request_stop();
  connections.clear();
}

void NetworkManager::LaunchConnectionBase() {
  // start event base loop for connection callbacks
  connection_base_thread = std::make_unique<std::jthread>(
    LaunchConnectionBaseHandler,
    this->connection_base
  );

  // start channel loop for reading incoming data from connection callbacks
  /*std::jthread channel_handler(
    LaunchChannelHandler,
    std::ref(this->connections_mutex),
    std::ref(this->in_chann),
    std::ref(this->connections)
  );*/
}

int NetworkManager::InitiateSecureConnection(const std::string &end_point_uuid, const std::string &service_uuid) {
  if (!connections.contains(end_point_uuid) || !connections.contains(service_uuid)) {
    printf("[NetworkManager]: connections do not exist\n");
    return -1;
  }

  auto end_point_conn = connections.at(end_point_uuid);  

  if (end_point_conn->IsSecure()) {
    printf("[NetworkManager]: end point already secure\n");
    return -1;
  }
  
  auto service_conn = connections.at(service_uuid);

  if (!service_conn->IsSecure()) {
    printf("[NetworkManager]: service not secure\n");
    return -1;
  }

  const std::string end_point_pk = end_point_conn->GetPublicKey();
  
  std::unique_ptr<Message> pk_msg = CreateServerStreamOutPublicKey(
    end_point_uuid,
    end_point_pk
  );

  // send our PK as plaintext
  if (service_conn->SendMessage(pk_msg.get()) < 0) {
    // failed to send PK
    return -1;
  }

  return 0;
}
  
int NetworkManager::CreateConnection(
  const ConnectionType type,
  const std::string &uuid,
  const std::string &ip_address,
  const std::string &port
) 
{
  if (connections.contains(uuid)) {
    printf("[NetworkManager]: connection loaded\n");
    return 0;
  }
 
  auto conn = GetConnection(
    type,
    connection_base,
    std::ref(in_chann),
    ip_address,
    port
  );

  if(conn == nullptr) {
    printf("[NetworkManager]: connection failed to create\n");
    return -1;
  }
  
  if (conn->Initiate()) {
    printf("[NetworkManager]: connection failed to initiate\n");
    return -1;
  }

  connections.insert(std::pair<std::string, std::shared_ptr<Connection>>(uuid, conn));
  
  printf("[NetworkManager]: connection created\n");
  return 0;
}

int NetworkManager::SendMessage(const std::string &uuid, std::string &data) {
  if (!connections.contains(uuid)) {
    return -1;
  }

  std::unique_ptr<Message> message;
  if (DeserializeStreamOut(message.get(), data) != 0) {
    return -1;
  }

  int sent_bytes = connections.at(uuid)->SendMessage(message.get());

  return sent_bytes;
}

int NetworkManager::SendClientMessage(
  const std::string &uuid,
  const std::string &time,
  const std::string &date,
  const std::string &data
)
{
  if (!connections.contains(uuid)) {
    return -1;
  }

  std::unique_ptr<Message> message = CreateClientStreamOutSendMessage(
    time,
    date,
    data
  );

  int sent_bytes = connections.at(uuid)->SendMessage(message.get());

  return sent_bytes;
}