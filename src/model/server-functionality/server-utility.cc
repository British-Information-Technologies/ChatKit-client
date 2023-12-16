#include "server-utility.h"

#include <memory>
#include <string>

#include "server-node.h"

using namespace model_server_functionality;
using namespace std;

map<const string, shared_ptr<ServerNode>>::iterator ServerUtility::Begin() {
    return server_list->GetBegin();
}

map<const string, shared_ptr<ServerNode>>::iterator ServerUtility::End() {
    return server_list->GetEnd();
}

bool ServerUtility::AddServer(const string& uuid, const string& name, const string& owner, const std::string& ip, const std::string& port) {
    ServerNode server_node(uuid, name, owner, ip, port);
    return server_list->AddServer(server_node);
}

bool ServerUtility::DeleteServer(const string& uuid) {
    return server_list->DeleteServer(uuid);
}

shared_ptr<ServerNode> ServerUtility::GetServer(const string& uuid) const {
    return server_list->GetServer(uuid);
}