//
//  DismissGroupNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "DismissGroupNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

DismissGroupNotificationContentPrototype DismissGroupNotificationContent::sPrototype;

MessagePayload DismissGroupNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("g", groupId);
    builder.setValue("o", operatorId);
    
    payload.binaryContent = builder.build();

    return payload;
}

void DismissGroupNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
}

MessageContent* DismissGroupNotificationContent::clone() const {
    DismissGroupNotificationContent *p = new DismissGroupNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    return p;
}

const MessageContentPrototype* DismissGroupNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string DismissGroupNotificationContent::digest() const {
    return getGroupNotificationUserName(operatorId) + " 销毁了群组";
}

std::string DismissGroupNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
