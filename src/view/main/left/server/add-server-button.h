#ifndef VIEW_MAIN_LEFT_SERVER_ADD_BUTTON_H_
#define VIEW_MAIN_LEFT_SERVER_ADD_BUTTON_H_

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"
#include <memory>

#include "view/observers/notifications/notification-observer.h"

class AddServerButton : public Gtk::Button {
private:
    const Glib::RefPtr<Gtk::Builder> refBuilder;

    std::unique_ptr<view::NotificationObserver> show_add_server;

protected:
    void on_clicked() override;

public:
    AddServerButton(
        BaseObjectType* cobject,
        const Glib::RefPtr<Gtk::Builder>& refBuilder,
        view::NotificationObserver* show_add_server);

    ~AddServerButton() = default;
};

#endif