#include "friend-api.h"

#include "friend-hashmap.h"

using namespace model_friend_functionality;

FriendAPI::FriendAPI() { friend_list = std::make_unique<FriendHashmap>(); }