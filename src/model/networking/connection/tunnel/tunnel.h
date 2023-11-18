#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_H_

#include <memory>
#include <string>
#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <msd/channel.hpp>

#include "model/networking/messages/message.h"

#include "model/networking/connection/tunnel/data-handler/data-handler.h"

#include "model/networking/connection/listener/event-listener.h"

namespace model {
  enum class TunnelType {
    Client,
    Server,
  };

  enum class Party {
    One,
    Two
  };

  class Tunnel {
    private:
      const TunnelType type;
  
      std::shared_ptr<Connection> connection;

      const std::string uuid;

    protected:
      const std::string ip_address;
      const std::string port;

      std::shared_ptr<bufferevent> bev;

      std::unique_ptr<unsigned char[]> public_key;
      std::unique_ptr<unsigned char[]> secret_key;
      
      std::shared_ptr<DataHandler> data_handler;
 
    private:
      void *GetInAddr(struct sockaddr *);

    protected:
      void SetState(DataHandler *);
      
      static std::tuple<unsigned char*, unsigned char*> GenerateKeyPair();
 
      Tunnel(
        const TunnelType type,
        std::shared_ptr<Connection> connection,
        const std::string &uuid,
        std::shared_ptr<struct event_base> base,
        const std::string &ip_address,
        const std::string &port,
        unsigned char *public_key,
        unsigned char *secret_key
      );

      virtual ~Tunnel() {}
    
    public:
      void SetBev(bufferevent *bev);

      const char* GetIpAddress();

      int GetPort();
      
      bool IsSecure();

      const TunnelType GetType();

      const std::string GetPublicKey();
      
      int Initiate();

      int EstablishSecureTunnel(Party party, const unsigned char *recv_pk);
      
      virtual int SendMessage(Message *message) = 0;

      std::string ReadMessage(std::string &data);
  };
}  // namespace model_networking

#endif