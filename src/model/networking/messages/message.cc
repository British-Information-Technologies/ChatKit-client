#include <iostream>
#include <magic_enum.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <sodium.h>
#include <string>

#include "message.h"

#include "stream-in/server/client-connected.h"
#include "stream-in/server/client-removed.h"
#include "stream-in/server/connected-clients.h"
#include "stream-in/server/connected.h"
#include "stream-in/server/disconnected.h"
#include "stream-in/server/error.h"
#include "stream-in/server/global-chat-messages.h"
#include "stream-in/server/global-message.h"
#include "stream-in/server/public-key.h"
#include "stream-in/server/user-message.h"

#include "stream-in/network/connecting.h"
#include "stream-in/network/error.h"
#include "stream-in/network/got-info.h"
#include "stream-in/network/request.h"

#include "stream-in/client/send-message.h"

#include "stream-out/server/disconnect.h"
#include "stream-out/server/get-clients.h"
#include "stream-out/server/get-messages.h"
#include "stream-out/server/public-key.h"
#include "stream-out/server/send-global-message.h"
#include "stream-out/server/send-message.h"

#include "stream-out/network/connect.h"
#include "stream-out/network/info.h"

#include "stream-out/client/send-message.h"

#include "internal/event-error.h"

#include "model/networking/utility/decode.h"

using namespace model;

using json = nlohmann::json;

namespace {
json isValidJson(const std::string& data) {
    try {
        json data_json = json::parse(data);

        if (!data_json.contains("type")) {
            // data is invalid, must have a type
            return nullptr;
        }

        return data_json;
    } catch (std::exception _) {
        return nullptr;
    }
}
}// namespace

Type Message::GetType() {
    return this->type;
}

std::unique_ptr<Message> model::CreateClientStreamOutSendMessage(
    const std::string& time,
    const std::string& date,
    const std::string& data) {
    return std::make_unique<client_stream_out::SendMessage>(time, date, data);
}

std::unique_ptr<Message> model::CreateServerStreamOutPublicKey(
    const std::string& to,
    const std::string& pk) {
    return std::make_unique<server_stream_out::PublicKey>(to, pk);
}

// Stream In
Message* model::DeserializeStreamIn(std::string& data) {
    // convert to message object
    Message* msg = model::DeserializeClientStreamIn(data);
    if (msg->GetType() != Type::EventError) {
        return msg;
    }

    delete msg;

    msg = model::DeserializeServerStreamIn(data);
    if (msg->GetType() != Type::EventError) {
        return msg;
    }

    delete msg;

    return model::DeserializeNetworkStreamIn(data);
}

Message* model::DeserializeServerStreamIn(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::Connected: {
        return new server_stream_in::Connected();
    }

    case Type::ConnectedClients: {
        json clients = data_json.at("clients");
        return new server_stream_in::ConnectedClients(clients);
    }

    case Type::GlobalChatMessages: {
        json messages = data_json.at("messages");
        return new server_stream_in::GlobalChatMessages(messages);
    }

    case Type::UserMessage: {
        std::string from = data_json.at("from");
        std::string content = data_json.at("content");
        return new server_stream_in::UserMessage(from, content);
    }

    case Type::GlobalMessage: {
        std::string from = data_json.at("from");
        std::string content = data_json.at("content");
        return new server_stream_in::GlobalMessage(from, content);
    }

    case Type::ClientConnected: {
        std::string id = data_json.at("id");
        std::string username = data_json.at("username");
        return new server_stream_in::ClientConnected(id, username);
    }

    case Type::ClientRemoved: {
        std::string id = data_json.at("id");
        return new server_stream_in::ClientRemoved(id);
    }

    case Type::Disconnected: {
        return new server_stream_in::Disconnected();
    }

    case Type::Error: {
        std::string err_msg = data_json.at("msg");
        return new server_stream_in::Error(err_msg);
    }

    case Type::PublicKey: {
        std::string from = data_json.at("from");
        std::string encoded_key = data_json.at("key");

        return new server_stream_in::PublicKey(from, encoded_key);
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamIn");
    }
    }
}

Message* model::DeserializeNetworkStreamIn(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::Request: {
        return new network_stream_in::Request();
    }

    case Type::GotInfo: {
        std::string server_name = data_json.at("server_name");
        std::string server_owner = data_json.at("server_owner");
        return new network_stream_in::GotInfo(server_name, server_owner);
    }

    case Type::Connecting: {
        return new network_stream_in::Connecting();
    }

    case Type::Error: {
        return new network_stream_in::Error();
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamIn");
    }
    }
}

Message* model::DeserializeClientStreamIn(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::SendMessage: {
        std::string time = data_json.at("time");
        std::string date = data_json.at("date");
        std::string content = data_json.at("content");
        return new client_stream_in::SendMessage(time, date, content);
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamIn");
    }
    }
}

// Stream Out
Message* model::DeserializeStreamOut(std::string& data) {
    // convert to message object
    Message* msg = model::DeserializeClientStreamOut(data);
    if (msg->GetType() != Type::EventError) {
        return msg;
    }

    delete msg;

    msg = model::DeserializeServerStreamOut(data);
    if (msg->GetType() != Type::EventError) {
        return msg;
    }

    delete msg;

    return model::DeserializeNetworkStreamOut(data);
}

Message* model::DeserializeServerStreamOut(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::GetClients: {
        return new server_stream_out::GetClients();
    }

    case Type::GetMessages: {
        return new server_stream_out::GetMessages();
    }

    case Type::SendMessage: {
        std::string to = data_json.at("to");
        std::string content = data_json.at("content");
        return new server_stream_out::SendMessage(to, content);
    }

    case Type::SendGlobalMessage: {
        std::string content = data_json.at("content");
        return new server_stream_out::SendGlobalMessage(content);
    }

    case Type::Disconnect: {
        return new server_stream_out::Disconnect();
    }

    case Type::PublicKey: {
        std::string to = data_json.at("to");
        std::string encoded_key = data_json.at("key");

        return new server_stream_out::PublicKey(to, encoded_key);
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamOut");
    }
    }
}

Message* model::DeserializeNetworkStreamOut(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::Info: {
        return new network_stream_out::Info();
    }

    case Type::Connect: {
        std::string uuid = data_json.at("uuid");
        std::string username = data_json.at("username");
        std::string address = data_json.at("address");
        return new network_stream_out::Connect(uuid, username, address);
        break;
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamOut");
    }
    }
}

Message* model::DeserializeClientStreamOut(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value_or(Type::EventError);

    switch (type) {
    case Type::SendMessage: {
        std::string time = data_json.at("time");
        std::string date = data_json.at("date");
        std::string content = data_json.at("content");
        return new client_stream_out::SendMessage(time, date, content);
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not StreamOut");
    }
    }
}

// Internal
Message* model::DeserializeInternal(std::string& data) {
    json data_json = isValidJson(data);
    if (data_json.is_null()) {
        return new internal::EventError("[DeserializeError]: message is not valid json");
    }

    auto type = magic_enum::enum_cast<Type>((std::string)data_json.at("type")).value();

    switch (type) {
    case Type::EventError: {
        std::string err_msg = data_json.at("msg");
        return new internal::EventError(err_msg);
    }

    default: {
        return new internal::EventError("[DeserializeError]: Message is not Internal");
    }
    }
}