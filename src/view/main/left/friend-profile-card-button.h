#ifndef VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_
#define VIEW_MAIN_LEFT_FRIEND_PROFILE_CARD_BUTTON_H_

#include <gtkmm-4.0/gtkmm.h>
#include <functional>

class FriendProfileCardButton : public Gtk::Button {
    private:
        Glib::RefPtr<Gtk::Builder> refBuilder;
        std::function<void()> setDirectMessageState;

    protected:
        void on_clicked();

    public:
        FriendProfileCardButton(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::function<void()> setDirectMessageState
        );
        virtual ~FriendProfileCardButton();
};

#endif