#include "error-callback.h"

#include <event2/buffer.h>
#include <event2/event.h>

using namespace controller_networking_callbacks;

void controller_networking_callbacks::ErrorCallback(struct bufferevent *bev,
                                                    short error, void *ctx) {
  if (error & BEV_EVENT_EOF) {
    /* connection has been closed, do any clean up here */
    /* ... */
  } else if (error & BEV_EVENT_ERROR) {
    /* check errno to see what error occurred */
    /* ... */
  } else if (error & BEV_EVENT_TIMEOUT) {
    /* must be a timeout event handle, handle it */
    /* ... */
  }
  bufferevent_free(bev);
}