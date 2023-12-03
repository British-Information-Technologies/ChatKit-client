#include "msd/channel.hpp"
#include <algorithm>
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <event2/bufferevent.h>
#include <event2/event.h>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <sodium.h>
#include <string>

#include "client-connection.h"

#include "model/networking/messages/message.h"

#include "model/networking/utility/buffer-reader.h"
#include "model/networking/utility/buffer-writer.h"
#include "model/networking/utility/data.h"

using namespace model;

int ClientConnection::GetRecipientPublicKey(unsigned char* recv_pk) {
    return 0;
}

ClientConnection::ClientConnection(
    const std::string& uuid,
    std::shared_ptr<event_base> base,
    msd::channel<Data>& network_manager_chann,
    const std::string& ip_address,
    const std::string& port,
    unsigned char* public_key,
    unsigned char* secret_key) : Connection(uuid, base, network_manager_chann, ip_address, port, public_key, secret_key) {}

std::shared_ptr<Connection> ClientConnection::Create(
    const std::string& uuid,
    std::shared_ptr<struct event_base> base,
    msd::channel<Data>& network_manager_chann,
    const std::string& ip_address,
    const std::string& port) {
    auto [public_key, secret_key] = GenerateKeyPair();

    if (public_key == nullptr || secret_key == nullptr) {
        return nullptr;
    }

    std::shared_ptr<Connection> conn(new ClientConnection(
        uuid,
        base,
        network_manager_chann,
        ip_address,
        port,
        public_key,
        secret_key));

    return conn;
}

int ClientConnection::SendMessage(Message* message) {
    if (message->GetStreamType() != StreamType::ClientStreamOut) {
        // message must be a client stream out
        return -1;
    }

    std::string msg_str = message->Serialize();
    std::string packet = data_handler->FormatSend(msg_str);

    if (!packet.length()) {
        // packet is empty, failed to format message
        return -1;
    }

    // send packet
    return WriteBufferLine(bev, packet);
}

void ClientConnection::ReadMessageCb() {
    // read packet
    std::string packet = ReadBufferLine(bev);

    // decode or decode and decrypt data
    std::string plaintext = data_handler->FormatRead(packet);

    if (!plaintext.length()) {
        // plaintext is empty, failed to format packet
        return;
    }

    std::cout << "[ClientConnection]: " << plaintext << std::endl;

    std::shared_ptr<Message> message(DeserializeClientStreamIn(plaintext));

    // send data to network manager
    SendChannelMessage(message);
}