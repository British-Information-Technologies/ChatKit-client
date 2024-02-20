#ifndef MODEL_NETWORKING_CONNECTION_TUNNEL_H_
#define MODEL_NETWORKING_CONNECTION_TUNNEL_H_

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <memory>
#include <msd/channel.hpp>
#include <string>

#include "model/networking/messages/message.h"

#include "model/networking/connection/tunnel/data-handler/data-handler.h"

#include "model/networking/connection/listener/event-listener.h"

namespace model {
class Connection;

enum class TunnelType {
    Client,
    Server,
};

enum class Party {
    One,
    Two
};

enum class TunnelState {
    None,
    Insecure,
    Secure
};

class Tunnel {
private:
    const TunnelType type;

    TunnelState state;

    std::shared_ptr<Connection> connection;

protected:
    const std::string ip_address;
    const std::string port;

    std::shared_ptr<bufferevent> bev;

    std::unique_ptr<unsigned char[]> public_key;
    std::unique_ptr<unsigned char[]> secret_key;

    std::shared_ptr<DataHandler> data_handler;

private:
    void* GetInAddr(struct sockaddr*);

protected:
    static std::tuple<unsigned char*, unsigned char*> GenerateKeyPair();

    Tunnel(
        const TunnelType type,
        std::shared_ptr<Connection> connection,
        std::shared_ptr<struct event_base> base,
        const std::string& ip_address,
        const std::string& port);

public:
    virtual ~Tunnel() = default;

    void SetBev(bufferevent* bev);

    int EnableBuffer();

    const char* GetIpAddress();

    int GetPort();

    void SetState(const TunnelState state);

    bool IsSecure();

    const TunnelType GetType();

    const std::string GetPublicKey();

    int Initiate();

    int EstablishSecureTunnel(Party party, const unsigned char* recv_pk);

    virtual int SendMessage(Message* message) = 0;

    std::string ReadMessage(std::string& data);
};
} // namespace model

#endif