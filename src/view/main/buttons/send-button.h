#ifndef VIEW_MAIN_BUTTONS_SEND_BUTTON_H_
#define VIEW_MAIN_BUTTONS_SEND_BUTTON_H_

#include <gtkmm-4.0/gtkmm.h>

#include "model/client-model.h"

class SendButton: public Gtk::Button {
    private:
        Glib::RefPtr<Gtk::Builder> refBuilder;
        std::shared_ptr<model::ClientModel> model;

    public:
        SendButton(
            BaseObjectType *cobject,
            const Glib::RefPtr<Gtk::Builder> &refBuilder,
            std::shared_ptr<model::ClientModel> model
        );

        virtual ~SendButton();

    protected:
        void on_clicked() override;
};

#endif