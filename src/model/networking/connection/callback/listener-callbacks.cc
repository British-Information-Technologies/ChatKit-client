#include "listener-callbacks.h"

#include <bits/stdc++.h>
#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>

#include "model/networking/connection/connection.h"
#include "model/networking/connection/callback/io-callbacks.h"

using namespace model;

void ListenerCallbacks::AcceptConnectionCbHandler(
  struct evconnlistener *listener,
  evutil_socket_t sockfd,
  struct sockaddr *address,
  int socklen,
  void *ptr
)
{
  // create new bufferevent and set its socket fd
  bufferevent *bev = bufferevent_socket_new(
    evconnlistener_get_base(listener),
    sockfd,
    BEV_OPT_CLOSE_ON_FREE
  );
  
  // free the listener, no longer needed as bev created
  evconnlistener_free(listener);

  // cast connection object
  Connection *connection = static_cast<Connection*>(ptr);

  // set connection callbacks
  switch (connection->GetType()) {
    case ConnectionType::Client:
      IOCallbacks::SetClientConnectionCallbacks(bev, connection);
      break;

    case ConnectionType::Server:
      IOCallbacks::SetServerConnectionCallbacks(bev, connection);
  }

  // enable the bufferevent read and write
  if (bufferevent_enable(bev, EV_READ|EV_WRITE) != 0) {
    // panic! failed to enable event socket read and write
    return;
  }
  
  // set connection bev
  connection->SetBev(bev);
  
  // finished listen
  std::cout << "[ListenerCallbacks]: connecting to " << address->sa_data << std::endl;
}

void ListenerCallbacks::AcceptErrorCbHandler(
  struct evconnlistener *listener,
  void *ptr
)
{
  int err = EVUTIL_SOCKET_ERROR();
  
  fprintf(stderr, "[ListenerCallbacks]: listener error = %d (%s)\n", err, evutil_socket_error_to_string(err));
  
  evconnlistener_free(listener);
}