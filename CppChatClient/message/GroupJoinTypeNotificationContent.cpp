//
//  GroupJoinTypeNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "GroupJoinTypeNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

GroupJoinTypeNotificationContentPrototype GroupJoinTypeNotificationContent::sPrototype;

MessagePayload GroupJoinTypeNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("n", type);
    payload.binaryContent = builder.build();
    return payload;
}

void GroupJoinTypeNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", type);
}

MessageContent* GroupJoinTypeNotificationContent::clone() const {
    GroupJoinTypeNotificationContent *p = new GroupJoinTypeNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->type = type;
    return p;
}

const MessageContentPrototype* GroupJoinTypeNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string GroupJoinTypeNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    if (type == "0") {
        result += " open join group";
    } else if(type == "1") {
        result += " allow member invite";
    } else {
        result += " close join group";
    }
    
    return result;
}

std::string GroupJoinTypeNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
