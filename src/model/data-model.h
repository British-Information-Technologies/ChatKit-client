#ifndef MODEL_DATA_MODEL_H_
#define MODEL_DATA_MODEL_H_

#include <memory>
#include <string>

#include "friend-functionality/friend-api.h"
#include "friend-functionality/friend-node.h"
#include "server-functionality/server-api.h"
#include "server-functionality/server-node.h"

namespace model {
    class DataModel {
        private:
            std::shared_ptr<model_friend_functionality::FriendAPI> friend_api;
            std::shared_ptr<model_server_functionality::ServerAPI> server_api;

        public:
            DataModel();
            
            bool AddFriend(const std::string &uuid, const std::string &name, const std::string &ip, const std::string &port);

            bool DeleteFriend(const std::string &uuid);

            std::shared_ptr<model_friend_functionality::FriendNode> GetFriend(
                const std::string &uuid) const;

            bool AddServer(const std::string &uuid, const std::string &name, const std::string &owner, const std::string &ip, const std::string &port);

            bool DeleteServer(const std::string &uuid);

            std::shared_ptr<model_server_functionality::ServerNode> GetServer(
                const std::string &uuid) const;
    };
}  // namespace model

#endif