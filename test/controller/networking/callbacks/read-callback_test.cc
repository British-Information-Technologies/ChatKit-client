#include <gtest/gtest.h>

#include <event2/event.h>
#include <assert.h>
#include <errno.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../../model/networking/temporary-server.h"

#include "../../../../src/controller/networking/callbacks/read-callback.h"
#include "../../../../src/controller/networking/callbacks/callback-collection.h"
#include "../../../../src/model/networking/connection.h"
#include "../../../../src/model/networking/server/server-connection.h"
#include "../../../../src/model/client-model.h"
#include "../../../../src/view/MainApplication.h"

using namespace model;
using namespace model_networking;
using namespace model_networking_server;
using namespace controller_networking_callbacks;

#define MAX_LINE 16384

class ReadCallbackTest : public ::testing::Test {
 private:
  std::shared_ptr<ClientModel> model;

  Glib::RefPtr<MainApplication> view;

  std::unique_ptr<struct event_base, decltype(&::event_base_free)> base_ptr;

  TemporaryServer *listen_server;

 protected:
  void SetUp() override {
    model = std::make_shared<ClientModel>();

    view = MainApplication::create();

    std::string ip_address = "localhost";
    std::string port = "3547";

    listen_server = new TemporaryServer(ip_address, port);

    int result = listen_server->SetUp();

    if (result  != 1) {
      fprintf(stderr, "server: setup failed\n");
      exit(1);
    }

    std::shared_ptr<model_networking::Connection> connection = std::make_shared<ServerConnection>(ip_address, port);

    int sockfd = connection->CreateConnection();
    if (sockfd == -1) {
      fprintf(stderr, "client: connection to server failed\n");
      exit(1);
    }

    struct CallbackCollection items {
        model, view, connection
    };

    event_base *base = base_ptr.get();

    base = event_base_new();
    if (!base) {
      fprintf(stderr, "client: message listener setup failed\n");
      exit(1);
    }

    struct bufferevent *bev;
    evutil_make_socket_nonblocking(sockfd);
    bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, ReadCallback, NULL, NULL, &items);
    bufferevent_setwatermark(bev, EV_READ, 0, MAX_LINE);
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    view->register_application();
  }

  void TearDown() override {
    event_base *base = base_ptr.get();

    event_base_loopexit(base, NULL);

    listen_server->TearDown();

    free(listen_server);
  }
};