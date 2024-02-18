#include "add-server-button.h"

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

AddServerButton::AddServerButton(
    BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& refBuilder,
    view::NotificationObserver* show_add_server)
    : Glib::ObjectBase("AddServerButton"),
      Gtk::Button(cobject),
      refBuilder(refBuilder),
      show_add_server(show_add_server) {}

void AddServerButton::on_clicked() {
    show_add_server->Notify("todo", "todo");
}