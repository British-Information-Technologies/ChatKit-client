#include "injector.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include <memory>

#include "view-model/network-view-model.h"
#include "view/common/ui-util.h"
#include "view/main/right/direct-message/direct-message-box.h"
#include "view/main/right/direct-message/message-entry.h"
#include "view/observers/workers/worker-observer.h"

const Glib::RefPtr<DirectMessage> injector::inject_direct_message_box(view::WorkerObserver* send_message) {
    Glib::RefPtr<Gtk::Builder> direct_message_builder = Gtk::Builder::create();

    view::UpdateBuilder(direct_message_builder, "/view/res/direct_message.ui");

    Glib::RefPtr<MessageEntry> message_entry = Glib::RefPtr<MessageEntry>(direct_message_builder->get_widget_derived<MessageEntry>(direct_message_builder, "messageEntry", send_message));

    return Glib::RefPtr<DirectMessage>(direct_message_builder->get_widget_derived<DirectMessage>(direct_message_builder, "directMessageBox", message_entry));
}