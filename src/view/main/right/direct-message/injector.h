#ifndef VIEW_MAIN_RIGHT_DIRECT_MESSAGE_INJECTOR_H_
#define VIEW_MAIN_RIGHT_DIRECT_MESSAGE_INJECTOR_H_

#include "glibmm/refptr.h"

#include "view-model/network-view-model.h"
#include "view/main/right/direct-message/direct-message-box.h"
#include "view/observers/workers/worker-observer.h"

namespace injector {
const Glib::RefPtr<DirectMessage> inject_direct_message_box(view::WorkerObserver* send_message);
} // namespace injector

#endif