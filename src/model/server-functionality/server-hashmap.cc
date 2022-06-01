#include "server-hashmap.h"

#include <memory>
#include <string>

#include "server-node.h"

using namespace model_server_functionality;
using namespace std;

std::map<const std::string, std::shared_ptr<ServerNode>>::iterator ServerHashmap::GetBegin() {
  return server_map.begin();
}

std::map<const std::string, std::shared_ptr<ServerNode>>::iterator ServerHashmap::GetEnd() {
  return server_map.end();
}

bool ServerHashmap::AddServer(ServerNode &server_node) {
  pair<map<const string, shared_ptr<ServerNode>>::iterator, bool> ret;
  string uuid = server_node.GetUuid();
  shared_ptr<ServerNode> server_ptr = make_shared<ServerNode>(server_node);

  ret = server_map.insert(
      pair<const string, shared_ptr<ServerNode>>(uuid, server_ptr));

  return ret.second;
}

bool ServerHashmap::DeleteServer(const string& uuid) {
  return server_map.erase(uuid);
}

shared_ptr<ServerNode> ServerHashmap::GetServer(const string& uuid) const {
  return server_map.at(uuid);
}