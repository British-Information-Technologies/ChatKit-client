#include <string>
#include <nlohmann/json.hpp>
#include <memory>
#include <sodium.h>
#include <magic_enum.hpp>

#include "message.h"

#include "stream-in/server/connected.h"
#include "stream-in/server/connected-clients.h"
#include "stream-in/server/global-chat-messages.h"
#include "stream-in/server/user-message.h"
#include "stream-in/server/global-message.h"
#include "stream-in/server/client-connected.h"
#include "stream-in/server/client-removed.h"
#include "stream-in/server/disconnected.h"
#include "stream-in/server/error.h"
#include "stream-in/server/public-key.h"

#include "stream-in/network/request.h"
#include "stream-in/network/got-info.h"
#include "stream-in/network/connecting.h"
#include "stream-in/network/error.h"

#include "stream-in/client/send-message.h"

#include "stream-out/server/get-clients.h"
#include "stream-out/server/get-messages.h"
#include "stream-out/server/send-message.h"
#include "stream-out/server/send-global-message.h"
#include "stream-out/server/disconnect.h"
#include "stream-out/server/public-key.h"

#include "stream-out/network/info.h"
#include "stream-out/network/connect.h"

#include "stream-out/client/send-message.h"

#include "internal/event-error.h"

#include "model/networking/utility/decode.h"

using namespace model;

using json = nlohmann::json;

namespace {
    json isValidJson(Message* msg, const std::string &data) {
        try {
            json data_json = json::parse(data);
            
            if (!data_json.contains("type")) {
                // data is invalid, must have a type
                msg = new internal::EventError("[DeserializeError]: Missing type, message is not valid json");
                return nullptr;
            }
            
            return data_json;
        } catch (std::exception _) {
            msg = new internal::EventError("[DeserializeError]: Parse error, message is not json");
            return nullptr;
        }
    }
} // namespace



Type Message::GetType() {
    return this->type;
}

std::unique_ptr<Message> model::CreateClientStreamOutSendMessage(
    const std::string &time,
    const std::string &date,
    const std::string &data
)
{
    return std::make_unique<client_stream_out::SendMessage>(time, date, data);
}

std::unique_ptr<Message> model::CreateServerStreamOutPublicKey(
    const std::string &to,
    const std::string &pk
)
{
    return std::make_unique<server_stream_out::PublicKey>(to, pk);
}

// Stream In
int model::DeserializeStreamIn(Message* msg, std::string &data) {
    // convert to message object
    if (
        model::DeserializeClientStreamIn(msg, data) &&
        model::DeserializeServerStreamIn(msg, data) &&
        model::DeserializeNetworkStreamIn(msg, data)
    ) {
        // data is invalid, non-existent stream in message type
        return -1;
    }

    // stream in message successfully created from data
    return 0;
}


int model::DeserializeServerStreamIn(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::Connected: {
            msg = new server_stream_in::Connected();
            break;
        }
        
        case Type::ConnectedClients: {
            json clients = data_json.at("clients");
            msg = new server_stream_in::ConnectedClients(clients);
            break;
        }

        case Type::GlobalChatMessages: {
            json messages = data_json.at("messages");
            msg = new server_stream_in::GlobalChatMessages(messages);
            break;
        }

        case Type::UserMessage: {
            std::string from = data_json.at("from");
            std::string content = data_json.at("content");
            msg = new server_stream_in::UserMessage(from, content);
            break;
        }

        case Type::GlobalMessage: {
            std::string from = data_json.at("from");
            std::string content = data_json.at("content");
            msg = new server_stream_in::GlobalMessage(from, content);
            break;
        }

        case Type::ClientConnected: {
            std::string id = data_json.at("id");
            std::string username = data_json.at("username");
            msg = new server_stream_in::ClientConnected(id, username);
            break;
        }

        case Type::ClientRemoved: {
            std::string id = data_json.at("id");
            msg = new server_stream_in::ClientRemoved(id);
            break;
        }

        case Type::Disconnected: {
            msg = new server_stream_in::Disconnected();
            break;
        }

        case Type::Error: {
            std::string err_msg = data_json.at("msg");
            msg = new server_stream_in::Error(err_msg);
            break;
        }

        case Type::PublicKey: {
            std::string from = data_json.at("from");
            std::string encoded_key = data_json.at("key");

            std::string key_str = Base642Bin(encoded_key);

            msg = new server_stream_in::PublicKey(from, key_str);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamIn");
            return -1;
        }
    }

    return 0;
}

int model::DeserializeNetworkStreamIn(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }

    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::Request: {
            msg = new network_stream_in::Request();
            break;
        }

        case Type::GotInfo: {
            std::string server_name = data_json.at("server_name");
            std::string server_owner = data_json.at("server_owner");
            msg = new network_stream_in::GotInfo(server_name, server_owner);
            break;
        }

        case Type::Connecting: {
            msg = new network_stream_in::Connecting();
            break;
        }

        case Type::Error: {
            msg = new network_stream_in::Error();
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamIn");
            return -1;
        }
    }

    return 0;
}

int model::DeserializeClientStreamIn(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::SendMessage: {
            std::string time = data_json.at("time");
            std::string date = data_json.at("date");
            std::string content = data_json.at("content");
            msg = new client_stream_in::SendMessage(time, date, content);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamIn");
            return -1;
        }
    }
    
    return 0;
}


// Stream Out
int model::DeserializeStreamOut(Message* msg, std::string &data) {
    // convert to message object
    if (
        model::DeserializeClientStreamOut(msg, data) &&
        model::DeserializeServerStreamOut(msg, data) &&
        model::DeserializeNetworkStreamOut(msg, data)
    ) {
        // data is invalid, non-existent stream out message type
        return -1;
    }

    // stream out message successfully created from data
    return 0;
}

int model::DeserializeServerStreamOut(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::GetClients: {
            msg = new server_stream_out::GetClients();
            break;
        }

        case Type::GetMessages: {
            msg = new server_stream_out::GetMessages();
            break;
        }

        case Type::SendMessage: {
            std::string to = data_json.at("to");
            std::string content = data_json.at("content");
            msg = new server_stream_out::SendMessage(to, content);
            break;
        }

        case Type::SendGlobalMessage: {
            std::string content = data_json.at("content");
            msg = new server_stream_out::SendGlobalMessage(content);
            break;
        }

        case Type::Disconnect: {
            msg = new server_stream_out::Disconnect();
            break;
        }

        case Type::PublicKey: {
            std::string to = data_json.at("to");
            std::string encoded_key = data_json.at("key");

            std::string key_str = Base642Bin(encoded_key);

            msg = new server_stream_out::PublicKey(to, key_str);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamOut");
            return -1;
        }
    }

    return 0;
}

int model::DeserializeNetworkStreamOut(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::Info: {
            msg = new network_stream_out::Info();
            break;
        }

        case Type::Connect: {
            std::string uuid = data_json.at("uuid");
            std::string username = data_json.at("username");
            std::string address = data_json.at("address");
            msg = new network_stream_out::Connect(uuid, username, address);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamOut");
            return -1;
        }
    }

    return 0;
}

int model::DeserializeClientStreamOut(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::SendMessage: {
            std::string time = data_json.at("time");
            std::string date = data_json.at("date");
            std::string content = data_json.at("content");
            msg = new client_stream_out::SendMessage(time, date, content);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not StreamOut");
            return -1;
        }
    }
    
    return 0;
}


// Internal
int model::DeserializeInternal(Message* msg, std::string &data) {
    json data_json = isValidJson(msg, data);
    if (data_json.is_null()) {
        return -1;
    }
    
    auto type = magic_enum::enum_cast<Type>(data_json.at("type"));
    if (!type.has_value()) {
        return -1;
    }

    switch (type.value()) {
        case Type::EventError: {
            std::string err_msg = data_json.at("msg");
            msg = new internal::EventError(err_msg);
            break;
        }

        default: {
            msg = new internal::EventError("[DeserializeError]: Message is not Internal");
            return -1;
        }
    }

    return 0;
}