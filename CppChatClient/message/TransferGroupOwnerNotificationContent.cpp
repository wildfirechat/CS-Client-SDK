//
//  TransferGroupOwnerNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "TransferGroupOwnerNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

TransferGroupOwnerNotificationContentPrototype TransferGroupOwnerNotificationContent::sPrototype;

MessagePayload TransferGroupOwnerNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("m", owner);
    payload.binaryContent = builder.build();
    return payload;
}

void TransferGroupOwnerNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("m", owner);
}

MessageContent* TransferGroupOwnerNotificationContent::clone() const {
    TransferGroupOwnerNotificationContent *p = new TransferGroupOwnerNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->owner = owner;
    return p;
}

const MessageContentPrototype* TransferGroupOwnerNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string TransferGroupOwnerNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    result += " 把群组转让给 ";
    result += getGroupNotificationUserName(owner);

    
    return result;
}

std::string TransferGroupOwnerNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
