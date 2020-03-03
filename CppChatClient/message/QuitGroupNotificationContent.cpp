//
//  QuitGroupNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "QuitGroupNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

QuitGroupNotificationContentPrototype QuitGroupNotificationContent::sPrototype;

MessagePayload QuitGroupNotificationContent::encode() const
{
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("g", groupId);
    builder.setValue("o", operatorId);
    
    payload.binaryContent = builder.build();

    return payload;
}

void QuitGroupNotificationContent::decode(const MessagePayload & payload)
{
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }

    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
}

MessageContent* QuitGroupNotificationContent::clone() const {
    QuitGroupNotificationContent *p = new QuitGroupNotificationContent();
    p->extra = extra;
    p->operatorId = operatorId;
    p->groupId = groupId;
    return p;
}

const MessageContentPrototype* QuitGroupNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string QuitGroupNotificationContent::digest() const {
    return getGroupNotificationUserName(operatorId) + " 退出了群组";
}

std::string QuitGroupNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
