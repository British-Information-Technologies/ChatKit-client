#include "injector.h"

#include <memory>
#include <string>
#include <msd/channel.hpp>

#include "model/networking/connection/connection.h"
#include "model/networking/connection/tunnel/tunnel-factory.h"
#include "model/networking/connection/listener/event-listener.h"
#include "model/networking/connection/channel/channel-writer.h"

using namespace model;

std::shared_ptr<Connection> Injector::inject_connection(
    const ConnectionType type,
    const std::string &uuid,
    std::shared_ptr<event_base> base,
    const std::string &ip_address,
    const std::string &port,
    msd::channel<model::Data> &output
)
{
    std::shared_ptr<Connection> connection = std::make_shared<Connection>();
    
    connection->tunnel = GetTunnel(
        type == ConnectionType::Client ? TunnelType::Client : TunnelType::Server,
        connection,
        uuid,
        base,
        ip_address,
        port
    );

    connection->listener = std::make_unique<EventListener>(new EventListener(
        base,
        connection
    ));

    connection->channel = std::make_unique<ChannelWriter>(new ChannelWriter(
        output,
        uuid
    ));
    
    return connection;
}