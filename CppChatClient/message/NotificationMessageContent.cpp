//
//  NotificationMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "NotificationMessageContent.h"
#include "../ChatClient.h"
#include "../model/UserInfo.h"

namespace WFCLib {
std::string NotificationMessageContent::getGroupNotificationUserName(const std::string &userId) const {
    if (userId == ChatClient::Instance()->getCurrentUserId()) {
        return "You";
    } else {
        UserInfo userInfo = ChatClient::Instance()->getUserInfo(userId, false);
        return userInfo.displayName;
    }
}

MessagePayload NotificationMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    return payload;
}

void NotificationMessageContent::decode(const MessagePayload &payload) {
    MessageContent::decode(payload);
}
};

