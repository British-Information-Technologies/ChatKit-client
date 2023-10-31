#include "event-listener.h"

#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <netdb.h>
#include <memory>
#include <string>

#include "model/networking/connection/connection.h"
#include "model/networking/connection/callback/listener-callbacks.h"

using namespace model;

EventListener::EventListener(
  std::shared_ptr<event_base> base,
  std::shared_ptr<Connection> connection
)
: base(base),
  connection(connection),
  state(EventListenerState::Idle),
  listener(nullptr)
{}

EventListener::~EventListener()
{
    if (listener) { evconnlistener_free(listener); }
}

void EventListener::Listen()
{
  struct sockaddr_in sin;
  
  // Clear the sockaddr in case extra platform-specific fields are messed up
  memset(&sin, 0, sizeof(sin));

  sin.sin_family = AF_INET; // add 6 for ipv6
  
  sin.sin_addr.s_addr = inet_addr(connection->GetIpAddress()); // listen on ip_address
  sin.sin_port = htons(connection->GetPort()); // listen on port

  if (listener) { evconnlistener_free(listener); }

  listener = evconnlistener_new_bind(
    base.get(),
    ListenerCallbacks::AcceptConnectionCbHandler,
    connection.get(),
    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
    -1,
    (struct sockaddr*)&sin,
    sizeof(sin)
  );
  
  SetState(EventListenerState::Listening);
  evconnlistener_set_error_cb(listener, ListenerCallbacks::AcceptErrorCbHandler);

  printf("[EventListener]: listener started\n");
}

void EventListener::SetState(EventListenerState state)
{
    this->state = state;
}

const EventListenerState EventListener::GetState()
{
    return state;
}