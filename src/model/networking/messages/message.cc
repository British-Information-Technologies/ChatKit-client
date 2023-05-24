#include <string>
#include <nlohmann/json.hpp>

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

#include "stream-in/network/request.h"
#include "stream-in/network/got-info.h"
#include "stream-in/network/connecting.h"
#include "stream-in/network/error.h"

#include "stream-out/server/get-clients.h"
#include "stream-out/server/get-messages.h"
#include "stream-out/server/send-message.h"
#include "stream-out/server/send-global-message.h"
#include "stream-out/server/disconnect.h"

#include "stream-out/network/info.h"
#include "stream-out/network/connect.h"

using namespace model_networking_messages;

using json = nlohmann::json;

std::string Message::GetType() {
    return this->type;
}

int Deserialize(Message* msg, std::string data, int is_stream_in) {
    json data_json = json::parse(data);

    if (!data_json.contains("type")) {
        // data is invalid, must have a type
        return -1;
    }

    // convert to message object
    if (is_stream_in  && (isServerStreamInMessage(msg, data_json) || isNetworkStreamInMessage(msg, data_json))) {
        // stream in message successfully created from data
        return 0;
    } else if (isServerStreamOutMessage(msg, data_json) || isNetworkStreamOutMessage(msg, data_json)) {
        // stream out message successfully created from data
        return 0;
    }

    // data is invalid, non-existent message type
    return -1;
}

int Deserialize(Message* msg, std::string data) {
    return Deserialize(msg, data, 1);
}


// internal linkage - functions are not referenced outside message.cc
namespace {
    int isServerStreamInMessage(Message* msg, const json data_json);
    int isNetworkStreamInMessage(Message* msg, const json data_json);

    int isServerStreamOutMessage(Message* msg, const json data_json);
    int isNetworkStreamOutMessage(Message* msg, const json data_json);


    int isServerStreamInMessage(Message* msg, const json data_json) {
        std::string type = data_json.at("type");
        
        if (type == server_stream_in::kConnected) {
            msg = new server_stream_in::Connected();

        } else if (type == server_stream_in::kConnectedClients && data_json.contains("clients")) {
            json clients = data_json.at("clients");
            msg = new server_stream_in::ConnectedClients(clients);

        } else if (type == server_stream_in::kGlobalChatMessages && data_json.contains("messages")) {
            json messages = data_json.at("messages");
            msg = new server_stream_in::GlobalChatMessages(messages);

        } else if (type == server_stream_in::kUserMessage && data_json.contains("from") && data_json.contains("content")) {
            std::string from = data_json.at("from");
            std::string content = data_json.at("content");
            msg = new server_stream_in::UserMessage(from, content);

        } else if (type == server_stream_in::kGlobalMessage && data_json.contains("from") && data_json.contains("content")) {
            std::string from = data_json.at("from");
            std::string content = data_json.at("content");
            msg = new server_stream_in::GlobalMessage(from, content);

        } else if (type == server_stream_in::kClientConnected && data_json.contains("id") && data_json.contains("username")) {
            std::string id = data_json.at("id");
            std::string username = data_json.at("username");
            msg = new server_stream_in::ClientConnected(id, username);
            
        } else if (type == server_stream_in::kClientRemoved && data_json.contains("id")) {
            std::string id = data_json.at("id");
            msg = new server_stream_in::ClientRemoved(id);

        } else if (type == server_stream_in::kDisconnected) {
            msg = new server_stream_in::Disconnected();

        } else if (type == server_stream_in::kError && data_json.contains("msg")) {
            std::string err_msg = data_json.at("msg");
            msg = new server_stream_in::Error(err_msg);

        } else {
            return 0;
        }

        return 1;
    }

    int isNetworkStreamInMessage(Message* msg, const json data_json) {
        std::string type = data_json.at("type");
        
        if (type == network_stream_in::kRequest) {
            msg = new network_stream_in::Request();

        } else if (type == network_stream_in::kGotInfo && data_json.contains("server_name") && data_json.contains("server_owner")) {
            std::string server_name = data_json.at("server_name");
            std::string server_owner = data_json.at("server_owner");
            msg = new network_stream_in::GotInfo(server_name, server_owner);

        } else if (type == network_stream_in::kConnecting) {
            msg = new network_stream_in::Connecting();

        } else if (type == network_stream_in::kError) {
            msg = network_stream_in::Error();

        } else {
            return 0;
        }

        return 1;
    }

    int isServerStreamOutMessage(Message* msg, const json data_json) {
        std::string type = data_json.at("type");
        
        if (type == server_stream_out::kGetClients) {
            msg = new server_stream_out::GetClients();

        } else if (type == server_stream_out::kGetMessages) {
            msg = new server_stream_out::GetMessages();

        } else if (type == server_stream_out::kSendMessage && data_json.contains("to") && data_json.contains("content")) {
            std::string to = data_json.at("to");
            std::string content = data_json.at("content");
            msg = new server_stream_out::SendMessage(to, content);

        } else if (type == server_stream_out::kSendGlobalMessage && data_json.contains("content")) {
            std::string content = data_json.at("content");
            msg = new server_stream_out::SendGlobalMessage(content);

        } else if (type == server_stream_out::kDisconnect) {
            msg = new server_stream_out::Disconnect();

        } else {
            return 0;
        }

        return 1;
    }

    int isNetworkStreamOutMessage(Message* msg, const json data_json) {
        std::string type = data_json.at("type");
        
        if (type == network_stream_out::kInfo) {
            msg = new network_stream_out::Info();

        } else if (type == network_stream_out::kConnect && data_json.contains("uuid") && data_json.contains("username") && data_json.contains("address")) {
            std::string uuid = data_json.at("uuid");
            std::string username = data_json.at("username");
            std::string address = data_json.at("address");
            msg = new network_stream_out::Connect(uuid, username, address);

        } else {
            return 0;
        }

        return 1;
    }
} // namespace