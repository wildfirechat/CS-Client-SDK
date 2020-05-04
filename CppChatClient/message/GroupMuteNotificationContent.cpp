//
//  GroupMuteNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "GroupMuteNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

GroupMuteNotificationContentPrototype GroupMuteNotificationContent::sPrototype;

MessagePayload GroupMuteNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("n", type);
    payload.binaryContent = builder.build();
    return payload;
}

void GroupMuteNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", type);
}

MessageContent* GroupMuteNotificationContent::clone() const {
    GroupMuteNotificationContent *p = new GroupMuteNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->type = type;
    return p;
}

const MessageContentPrototype* GroupMuteNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string GroupMuteNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    if (type == "1") {
        result += " mute group chat";
    } else {
        result += " unmute group chat";
    }
    
    return result;
}

std::string GroupMuteNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
