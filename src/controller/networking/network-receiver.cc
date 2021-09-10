#include "network-receiver.h"

#include <assert.h>
#include <errno.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../model/message-functionality/message.h"
#include "callbacks/error-callback.h"
#include "callbacks/read-callback.h"

using namespace model_message_functionality;
using namespace std;
using namespace model;
using namespace controller_networking;
using namespace model_networking;
using namespace controller_networking_callbacks;

#define MAX_LINE 16384

NetworkReceiver::NetworkReceiver(
    shared_ptr<ClientModel> model, Glib::RefPtr<MainApplication> view,
    shared_ptr<unordered_map<int, shared_ptr<Connection>>> connection) {
  this->model = model;
  this->view = view;
  this->connections = connections;
}

NetworkReceiver::~NetworkReceiver() {}

void NetworkReceiver::listen() {
  struct event_base *base;
  base = event_base_new();
  if (!base) {
    return;
  }

  for (auto connection : *connections.get()) {
    int sockfd = connection.first;

    struct bufferevent *bev;
    evutil_make_socket_nonblocking(sockfd);
    bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, ReadCallback, NULL, ErrorCallback,
                      &connection.second);
    bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
    bufferevent_enable(bev, EV_READ | EV_WRITE);
  }

  event_base_dispatch(base);
}