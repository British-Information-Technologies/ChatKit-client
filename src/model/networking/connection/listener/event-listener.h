#ifndef MODEL_NETWORKING_CONNECTION_LISTENER_H_
#define MODEL_NETWORKING_CONNECTION_LISTENER_H_

#include <event2/bufferevent.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <memory>
#include <string>

namespace model {
class Connection;

enum class EventListenerState {
    Idle,
    Listening
};

class EventListener {
private:
    std::shared_ptr<event_base> base;

    std::shared_ptr<Connection> connection;

    EventListenerState state;

    evconnlistener* listener;

public:
    EventListener(
        std::shared_ptr<event_base> base,
        std::shared_ptr<Connection> connection);

    ~EventListener();

    void Listen();

    void SetState(EventListenerState state);

    const EventListenerState GetState();

    const bool IsListening();
};
} // namespace model

#endif