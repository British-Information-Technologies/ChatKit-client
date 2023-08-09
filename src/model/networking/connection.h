#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <memory>
#include <string>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <nlohmann/json.hpp>
#include "msd/channel.hpp"

#include "messages/message.h"
#include "utility/data-handler.h"

using json = nlohmann::json;

namespace model {
  class Connection {
    protected:
      std::string ip_address;
      std::string port;

      std::shared_ptr<bufferevent> bev;

      std::unique_ptr<unsigned char[]> pk;
      std::unique_ptr<unsigned char[]> sk;
      
      std::unique_ptr<DataHandler> data_handler;

      msd::channel<json> &out_chann;
 
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
      void SetState(DataHandler *);
    
    public:
      Connection(std::shared_ptr<struct event_base> base, msd::channel<json> &network_manager_chann, const std::string &ip_address, const std::string &port);

      ~Connection();
      
      int CreateConnection();

      int SendPublicKey();

      int EstablishSecureConnection(const unsigned char *recv_pk);

      virtual int SendMessage(Message *message) = 0;
  };
}  // namespace model_networking

#endif