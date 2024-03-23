#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <memory>
#include <string>

#include "network-view-model.h"

#include "model/network-model.h"
#include "view/observers/notifications/notification-observer.h"
#include "view/observers/server-observables.h"

using namespace view_model;
using namespace view;

NetworkViewModel::NetworkViewModel(
    std::unique_ptr<model::NetworkModel> model)
    : model(std::move(model)) {}

void NetworkViewModel::ConnectToServer(
    const std::string& ip_address,
    const std::string& port,
    view::ServerObservables* observables) {
    const std::string fake_uuid = "micky_server"; // TODO: replace
    if (model->CreateServerConnection(fake_uuid, ip_address, port) != 0) {
        return;
    };

    model->SetNotification(fake_uuid, observables);

    model->EnableBuffer(fake_uuid); // todo: maybe move back to create connection
}

void NetworkViewModel::ConnectToClient(
    const std::string& ip_address,
    const std::string& port,
    view::NotificationObserver* notification) {
    const std::string fake_uuid = "faked uuid"; // TODO: currently faked, will use data model getUuid() or server,

    if (model->CreateClientConnection(fake_uuid, ip_address, port) != 0) {
        return;
    }

    //model->SetNotification(fake_uuid, notification);

    //model->EnableBuffer(fake_uuid);
}

int NetworkViewModel::SendMessage(const std::string& uuid, const std::string& data) {
    const std::string time("fake time"); // TODO
    const std::string date("fake date"); // TODO

    return model->SendClientMessage(uuid, time, date, data);
}