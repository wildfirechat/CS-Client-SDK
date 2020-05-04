//
//  ChangeGroupNameNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ChangeGroupNameNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

ChangeGroupNameNotificationContentPrototype ChangeGroupNameNotificationContent::sPrototype;

MessagePayload ChangeGroupNameNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("n", name);
    payload.binaryContent = builder.build();
    return payload;
}

void ChangeGroupNameNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", name);
}

MessageContent* ChangeGroupNameNotificationContent::clone() const {
    ChangeGroupNameNotificationContent *p = new ChangeGroupNameNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->name = name;
    return p;
}

const MessageContentPrototype* ChangeGroupNameNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string ChangeGroupNameNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    result += " 修改群名为： ";
    result += name;
    
    return result;
}

std::string ChangeGroupNameNotificationContent::formatNotification(const Message &msg) const {
    return "";
}
};
