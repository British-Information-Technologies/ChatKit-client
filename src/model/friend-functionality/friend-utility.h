#ifndef MODEL_FRIEND_FUNCTIONALITY_FRIEND_UTILITY_H_
#define MODEL_FRIEND_FUNCTIONALITY_FRIEND_UTILITY_H_

#include <memory>
#include <string>

#include "friend-api.h"
#include "friend-node.h"

namespace model_friend_functionality {
class FriendUtility : public FriendAPI {
public:
    std::map<const std::string, std::shared_ptr<FriendNode>>::iterator Begin();
    std::map<const std::string, std::shared_ptr<FriendNode>>::iterator End();

    bool AddFriend(const std::string& uuid, const std::string& name, const std::string& ip, const std::string& port);
    bool DeleteFriend(const std::string& uuid);
    std::shared_ptr<FriendNode> GetFriend(const std::string& uuid) const;
};
} // namespace model_friend_functionality

#endif