#include "network-receiver.h"

#include <assert.h>
#include <errno.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpp-chat-client/model/message-functionality/message.h"
#include "callbacks/callback-collection.h"
#include "callbacks/error-callback.h"
#include "callbacks/read-callback.h"

using namespace model_message_functionality;
using namespace std;
using namespace model;
using namespace controller_networking;
using namespace model_networking;
using namespace controller_networking_callbacks;

#define MAX_LINE 16384

void NetworkReceiver::Listen(
    unordered_map<int, shared_ptr<Connection>> connections) {
  event_base *base = base_ptr.get();

  base = event_base_new();
  if (!base) return;

  for (auto connection : connections) {
    int sockfd = connection.first;

    struct CallbackCollection items {
      model, view, connection.second
    };

    struct bufferevent *bev;
    evutil_make_socket_nonblocking(sockfd);
    bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, ReadCallback, NULL, ErrorCallback, &items);
    bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
  }

  event_base_dispatch(base);
}

int NetworkReceiver::Stop() {
  event_base *base = base_ptr.get();

  return event_base_loopexit(base, NULL);
}

void NetworkReceiver::InternalThreadEntry() {
  auto connections = model->LoadConnections();

  Listen(connections);
}

NetworkReceiver::NetworkReceiver(shared_ptr<ClientModel> model,
                                 Glib::RefPtr<MainApplication> view)
    : base_ptr(event_base_new(), ::event_base_free) {
  this->model = model;
  this->view = view;
}

NetworkReceiver::~NetworkReceiver() {}

void NetworkReceiver::WaitForInternalThreadToExit() {
  int result = Stop();

  thread_wrapper::Thread::WaitForInternalThreadToExit();
}