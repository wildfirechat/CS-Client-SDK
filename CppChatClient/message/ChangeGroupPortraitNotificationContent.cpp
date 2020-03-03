//
//  ChangeGroupPortraitNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ChangeGroupPortraitNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

ChangeGroupPortraitNotificationContentPrototype ChangeGroupPortraitNotificationContent::sPrototype;

MessagePayload ChangeGroupPortraitNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("n", portrait);
    payload.binaryContent = builder.build();
    return payload;
}

void ChangeGroupPortraitNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", portrait);
}

MessageContent* ChangeGroupPortraitNotificationContent::clone() const {
    ChangeGroupPortraitNotificationContent *p = new ChangeGroupPortraitNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->portrait = portrait;
    return p;
}

const MessageContentPrototype* ChangeGroupPortraitNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string ChangeGroupPortraitNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    result += " 更改了群头像";
    
    return result;
}

std::string ChangeGroupPortraitNotificationContent::formatNotification(const Message &msg) const {
    return "";
}
};
