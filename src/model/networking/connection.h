#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <memory>
#include <string>
#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <msd/channel.hpp>

#include "messages/message.h"
#include "utility/data-handler.h"
#include "utility/data.h"

namespace model {
  class Connection {
    private:
      const std::string uuid;

      evconnlistener *listener;

      msd::channel<Data> &out_chann;

    protected:
      const std::string ip_address;
      const std::string port;

      std::shared_ptr<bufferevent> bev;

      std::unique_ptr<unsigned char[]> pk;
      std::unique_ptr<unsigned char[]> sk;
      
      std::unique_ptr<DataHandler> data_handler;
 
    private:
      void *GetInAddr(struct sockaddr *);

      static void AcceptConnectionCbHandler(
        struct evconnlistener *listener,
        evutil_socket_t sockfd,
        struct sockaddr *address,
        int socklen,
        void *ptr
      );
      void AcceptConnectionCb(evutil_socket_t sockfd, struct sockaddr *address);

      static void AcceptErrorCbHandler(struct evconnlistener *listener, void *ptr);
      void AcceptErrorCb();

      static void ReadMessageCbHandler(struct bufferevent *bev, void *ptr);
      virtual void ReadMessageCb() = 0;
      
      static void WriteMessageCbHandler(struct bufferevent *bev, void *ptr);
      void WriteMessageCb();

      static void EventCbHandler(struct bufferevent *bev, short events, void *ptr);
      void EventCb(short events);
      
      virtual int GetRecipientPublicKey(unsigned char* recv_pk) = 0;
    
    protected:
      void SetState(DataHandler *);
      
      static std::tuple<unsigned char*, unsigned char*> GenerateKeyPair();

      void SendChannelMessage(std::shared_ptr<Message> message);
      
      Connection(
        const std::string &uuid,
        std::shared_ptr<struct event_base> base,
        msd::channel<Data> &network_manager_chann,
        const std::string &ip_address,
        const std::string &port,
        unsigned char *pk,
        unsigned char *sk
      );

      virtual ~Connection();
    
    public:
      bool IsSecure();

      const std::string GetPublicKey();
      
      int Initiate();

      void Listen(std::shared_ptr<event_base> base);

      int EstablishSecureConnection(const unsigned char *recv_pk);
      
      virtual int SendMessage(Message *message) = 0;
  };
}  // namespace model_networking

#endif