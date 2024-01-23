#include <functional>
#include <gtkmm-4.0/gtkmm.h>
#include <iostream>
#include <memory>
#include <string>

#include "network-view-model.h"

#include "model/network-model.h"
#include "view/observers/notifications/notification-observer.h"

using namespace view_model;
using namespace view;

NetworkViewModel::NetworkViewModel(
    std::unique_ptr<model::NetworkModel> model,
    std::function<void()> showDirectMessage) : model(std::move(model)), showDirectMessage(showDirectMessage) {}

void NetworkViewModel::ConnectToServer(
    const std::string& ip_address,
    const std::string& port,
    view::NotificationObserver* notification) {
    const std::string fake_uuid = "micky_server"; // TODO: replace
    if (model->CreateServerConnection(fake_uuid, ip_address, port) != 0) {
        return;
    }

    model->SetNotification(fake_uuid, notification);

    model->EnableBuffer(fake_uuid);
}

void NetworkViewModel::SendMessageObserver(std::string& data) {
    if (data.empty()) {
        return;
    }

    std::cout << "Message to send: " << data << std::endl;

    const std::string time("fake time"); // TODO
    const std::string date("fake date"); // TODO

    model->SendClientMessage("faked uuid", time, date, data); // TODO: currently faked, will use data model getUuid() or server,
}

void NetworkViewModel::OpenContactObserver() {
    model->CreateClientConnection(
        "faked uuid",   // TODO: currently faked, will use data model getUuid() or server,
        "192.168.0.59", // TODO: currently faked, will use data model getIpAddress() or server,
        "5789"          // TODO: currently faked, will use data model getPort() or server
    );

    showDirectMessage();
}