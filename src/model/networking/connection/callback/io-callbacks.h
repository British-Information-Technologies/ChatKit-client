#ifndef MODEL_NETWORKING_CONNECTION_CALLBACK_IO_H_
#define MODEL_NETWORKING_CONNECTION_CALLBACK_IO_H_

#include <event2/bufferevent.h>
#include <event2/event.h>

#include "model/networking/connection/connection.h"

namespace model_networking_connection_callback {
void SetClientConnectionCallbacks(
    struct bufferevent* bev,
    model::Connection* connection);

void SetServerConnectionCallbacks(
    struct bufferevent* bev,
    model::Connection* connection);
} // namespace model_networking_connection_callback

#endif