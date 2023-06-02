#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <string>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include "msd/channel.hpp"

#include "messages/message.h"
#include "utility/data-handler.h"

namespace model {
  class Connection {
    protected:
      std::string ip_address;
      std::string port;

      DataHandler *data_handler;

      struct bufferevent *bev;

      msd::channel<std::string> &out_chann;
 
    private:
      void *GetInAddr(struct sockaddr *);
       
      static void ReadMessageCbHandler(struct bufferevent *bev, void *ptr);
      void ReadMessageCb();
      
      static void WriteMessageCbHandler(struct bufferevent *bev, void *ptr);
      void WriteMessageCb();

      static void EventCbHandler(struct bufferevent *bev, short events, void *ptr);
      void EventCb(short events);
      
      virtual int GetRecipientPublicKey(unsigned char* recv_pk) = 0;
    
    protected:
      int CreateConnection();
      
      void SetState(DataHandler *);
    
    public:
      Connection(struct event_base *base, msd::channel<std::string> &network_manager_chann, const std::string &ip_address, const std::string &port);

      ~Connection();
      
      // virtual int SendPublicKey() = 0;

      virtual int EstablishSecureConnection() = 0;

      int SendMessage(Message *message);
  };
}  // namespace model_networking

#endif