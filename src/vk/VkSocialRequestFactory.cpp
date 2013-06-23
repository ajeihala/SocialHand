#include "VkSocialRequestFactory.h"

#include "vk/VKGetFriends.h"

VkSocialRequestFactory::VkSocialRequestFactory()
{
}

GetFriendsRequest* VkSocialRequestFactory::createGetFriendsRequest()
{
    return new VKGetFriends();
}
