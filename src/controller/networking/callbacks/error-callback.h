#ifndef CONTROLLER_NETWORKING_CALLBACKS_ERROR_CALLBACK_H_
#define CONTROLLER_NETWORKING_CALLBACKS_ERROR_CALLBACK_H_

#include <event2/bufferevent.h>

namespace controller_networking_callbacks {
void ErrorCallback(struct bufferevent *bev, short error, void *ctx);
}

#endif