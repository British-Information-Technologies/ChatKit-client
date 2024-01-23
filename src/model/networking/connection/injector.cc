#include "injector.h"

#include <memory>
#include <msd/channel.hpp>
#include <string>

#include "model/networking/connection/channel/channel-writer.h"
#include "model/networking/connection/connection.h"
#include "model/networking/connection/listener/event-listener.h"
#include "model/networking/connection/tunnel/tunnel-factory.h"

using namespace model;

std::shared_ptr<Connection> Injector::inject_connection(
    const ConnectionType type,
    const std::string& uuid,
    std::shared_ptr<event_base> base,
    const std::string& ip_address,
    const std::string& port,
    std::shared_ptr<ChannelWriter> buffer_writer) {
    std::shared_ptr<Connection> connection = std::make_shared<Connection>();

    connection->uuid = uuid;

    connection->tunnel = GetTunnel(
        type == ConnectionType::Client ? TunnelType::Client : TunnelType::Server,
        connection,
        base,
        ip_address,
        port);

    connection->listener.reset(new EventListener(
        base,
        connection));

    connection->channel = std::move(buffer_writer);

    connection->state = ConnectionState::NeedInfo;

    return connection;
}