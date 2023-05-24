#ifndef MODEL_NETWORKING_CONNECTION_H_
#define MODEL_NETWORKING_CONNECTION_H_

#include <string>

#include "messages/message.h"
#include "utility/socket-handler.h"

namespace model {
  class Connection {
    protected:
      std::string ip_address;
      std::string port;

      SocketHandler *socket_handler;

      int sockfd;
 
    private:
      void *GetInAddr(struct sockaddr *);
      
      virtual int GetRecipientPublicKey(unsigned char* recv_pk) = 0;
      
      virtual void SetState(SocketHandler *) = 0;
    
    protected:
      int CreateConnection();
    
    public:
      Connection(const std::string &ip_address, const std::string &port);

      ~Connection();

      virtual int SendPublicKey() = 0;

      virtual int EstablishSecureConnection() = 0;

      virtual int SendMessage(std::string &) = 0;

      virtual std::unique_ptr<Message> ReadMessage() = 0;
  };
}  // namespace model_networking

#endif