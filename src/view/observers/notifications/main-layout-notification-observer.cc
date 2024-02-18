#include "main-layout-notification-observer.h"

#include "view-model/network-view-model.h"
#include "view/observers/notifications/notification-observer.h"

#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include <string>

using namespace view;

MainLayoutNotificationObserver::MainLayoutNotificationObserver(
    Glib::RefPtr<Gtk::Box> main_box,
    Glib::RefPtr<Gtk::Box> sub_box_one,
    Glib::RefPtr<Gtk::Box> sub_box_two,
    Glib::RefPtr<Gtk::Box> sub_box_three)
    : NotificationObserver(),
      main_box(main_box),
      sub_box_one(sub_box_one),
      sub_box_two(sub_box_two),
      sub_box_three(sub_box_three) {}

void MainLayoutNotificationObserver::Notify(const std::string& alias, const std::string& owner) {
    sub_box_one->hide();
    sub_box_two->hide();
    sub_box_three->hide();
    main_box->show();

    // todo set direct message info with alias and owner
}