#include "VkSocialRequestFactory.h"

#include "vk/VKGetFriends.h"

VkSocialRequestFactory::VkSocialRequestFactory()
{
}

std::shared_ptr<SocialRequest> VkSocialRequestFactory::createGetFriendsRequest(const User& user)
{
    return std::make_shared<VKGetFriends>(user);
}
