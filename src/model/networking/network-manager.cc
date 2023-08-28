#include <sodium.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <event2/event.h>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
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
    printf("[NetworkManager]: connection base shutting down\n");
  }

  void LaunchInputChannelHandler(
    std::mutex &connections_mutex,
    msd::channel<Data> &in_chann,
    std::unordered_map<std::string, std::shared_ptr<Connection>> &connections
  ) {
    std::cout << "[NetworkManager]: input channel handler launched" << std::endl;

    // read incoming channel data from connection callbacks
    for (auto data: in_chann) { // blocks waiting for channel items
      std::cout << "[NetworkManager]: recv channel data from sockfd " << data.sockfd << std::endl;

      switch (data.message->GetType()) {
        case Type::PublicKey: {
          server_stream_in::PublicKey *recv_pk = dynamic_cast<server_stream_in::PublicKey*>(data.message.get());

          std::string end_point_uuid = recv_pk->GetFrom();

          auto end_point_conn = connections.at(end_point_uuid);

          if (end_point_conn->IsSecure()) {
            std::cout << "[NetworkManager]: connection " << end_point_uuid << " already secure" << std::endl;
            continue;
          }

          auto pk = CreateServerStreamOutPublicKey(end_point_uuid, end_point_conn->GetPublicKey());

          // ask service connection to send our pk to end point connection
          connections.at(data.uuid)->SendMessage(pk.get());

          // use received public key to create shared secret
          const unsigned char* recv_pk_ptr = reinterpret_cast<const unsigned char*>(recv_pk->GetKey().c_str());
          if (end_point_conn->EstablishSecureConnection(recv_pk_ptr) != 0) {
            std::cout << "[NetworkManager]: secure connection with " << end_point_uuid << " failed" << std::endl;
            // panic! failed to create secure connection
            continue;
          }

          std::cout << "[NetworkManager]: secure connection with " << end_point_uuid << " established" << std::endl;
          break;
        }

        case Type::EventError: {
          std::unique_ptr<internal::EventError> err(dynamic_cast<internal::EventError*>(data.message.get()));

          std::cout << "[NetworkManager]: EventError msg " << err->GetMsg() << std::endl;
          break;
        }

        default: {
        }
      }
    }

    std::cout << "[NetworkManager]: input channel handler shutting down" << std::endl;
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
  channel_thread->request_stop();
  connections.clear();
}

void NetworkManager::LaunchConnectionBase() {
  // start event base loop for connection callbacks
  connection_base_thread = std::make_unique<std::jthread>(
    LaunchConnectionBaseHandler,
    this->connection_base
  );
}

void NetworkManager::LaunchInputChannel() {
  // start channel loop for reading incoming data from connection callbacks
  channel_thread = std::make_unique<std::jthread>(
    LaunchInputChannelHandler,
    std::ref(this->connections_mutex),
    std::ref(this->in_chann),
    std::ref(this->connections)
  );
}

int NetworkManager::LaunchListener(const std::string &uuid) {
  if (!connections.contains(uuid)) {
    printf("[NetworkManager]: connection does not exist\n");
    return -1;
  }

  auto conn = connections.at(uuid);
  
  printf("[NetworkManager]: starting connection listener\n");
  conn->Listen(connection_base);

  return 0;
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

  // TODO Note: comment out for python test server
  //if (!service_conn->IsSecure()) {
  //  printf("[NetworkManager]: service not secure\n");
  //  return -1;
  //}

  const std::string end_point_pk = end_point_conn->GetPublicKey();
  
  std::unique_ptr<Message> pk_msg = CreateServerStreamOutPublicKey(
    end_point_uuid,
    end_point_pk
  );

  // send our PK as plaintext
  if (service_conn->SendMessage(pk_msg.get()) < 0) {
    // failed to send PK
    printf("[NetworkManager]: failed to send public key\n");
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
    uuid,
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
  //conn->Initiate();

  connections.insert(std::pair<std::string, std::shared_ptr<Connection>>(uuid, conn));
  
  printf("[NetworkManager]: connection created\n");
  return 0;
}

int NetworkManager::SendMessage(const std::string &uuid, std::string &data) {
  if (!connections.contains(uuid)) {
    return -1;
  }

  std::unique_ptr<Message> message(DeserializeStreamOut(data));

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