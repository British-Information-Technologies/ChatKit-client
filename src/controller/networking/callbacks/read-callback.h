#ifndef CONTROLLER_NETWORKING_CALLBACKS_READ_CALLBACK_H_
#define CONTROLLER_NETWORKING_CALLBACKS_READ_CALLBACK_H_

#include <event2/bufferevent.h>

namespace controller_networking_callbacks {
void ReadCallback(struct bufferevent *bev, void *ctx);
}

#endif