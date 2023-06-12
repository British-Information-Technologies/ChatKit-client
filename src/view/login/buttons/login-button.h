#ifndef VIEW_LOGIN_BUTTONS_LOGIN_BUTTON_H_
#define VIEW_LOGIN_BUTTONS_LOGIN_BUTTON_H_

#include <gtkmm-4.0/gtkmm.h>

class LoginButton: public Gtk::Button {
    private:
        Glib::RefPtr<Gtk::Builder> refBuilder;

    public:
        LoginButton(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder
        );

        virtual ~LoginButton();

    protected:
        void on_clicked() override;
};

#endif