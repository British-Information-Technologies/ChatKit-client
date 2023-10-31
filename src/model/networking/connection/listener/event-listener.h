#ifndef MODEL_NETWORKING_CONNECTION_LISTENER_H_
#define MODEL_NETWORKING_CONNECTION_LISTENER_H_

#include <event2/listener.h>
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <memory>
#include <string>

#include "model/networking/connection/connection.h"

namespace model {
    enum class EventListenerState {
        Idle,
        Listening,
        Finished
    };

    class EventListener {
        private:
            std::shared_ptr<event_base> base;
            
            std::shared_ptr<Connection> connection;
            
            EventListenerState state;

            evconnlistener *listener;

        public:
            EventListener(
                std::shared_ptr<event_base> base,
                std::shared_ptr<Connection> connection
            );

            virtual ~EventListener();

            void Listen();

            void SetState(EventListenerState state);

            const EventListenerState GetState();
    };
}

#endif