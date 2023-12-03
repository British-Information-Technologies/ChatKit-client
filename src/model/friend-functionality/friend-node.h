#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_NODE_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_NODE_H_

#include <string>

namespace model_friend_functionality {
class FriendNode {
private:
    std::string uuid;
    std::string name;
    std::string ip;
    std::string port;

public:
    FriendNode(const std::string& uuid, const std::string& name, const std::string& ip, const std::string& port);

    std::string GetUuid();

    std::string GetName();

    std::string GetIp();

    std::string GetPort();
};
}// namespace model_friend_functionality

#endif