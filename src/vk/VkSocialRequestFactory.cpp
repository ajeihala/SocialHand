#include "VkSocialRequestFactory.h"

#include "vk/VkGetUserInfoRequest.h"
#include "vk/VKGetFriendsRequest.h"

VkSocialRequestFactory::VkSocialRequestFactory(std::shared_ptr<AuthManager> authManager)
    : SocialRequestFactory(authManager)
{
}

std::shared_ptr<SocialRequest> VkSocialRequestFactory::createGetUserInfoRequest(const User& user)
{
    return setupRequest(std::make_shared<VkGetUserInfoRequest>(user));
}

std::shared_ptr<SocialRequest> VkSocialRequestFactory::createGetFriendsRequest(const User& user)
{
    return setupRequest(std::make_shared<VKGetFriendsRequest>(user));
}
