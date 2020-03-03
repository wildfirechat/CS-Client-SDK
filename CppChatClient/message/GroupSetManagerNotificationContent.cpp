//
//  GroupSetManagerNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "GroupSetManagerNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

GroupSetManagerNotificationContentPrototype GroupSetManagerNotificationContent::sPrototype;

MessagePayload GroupSetManagerNotificationContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("o", operatorId);
    builder.setValue("g", groupId);
    builder.setValue("n", type);
    builder.setValue("ms", memberIds);
    payload.binaryContent = builder.build();
    return payload;
}

void GroupSetManagerNotificationContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", type);
    parser.getValue("ms", memberIds);
}

MessageContent* GroupSetManagerNotificationContent::clone() const {
    GroupSetManagerNotificationContent *p = new GroupSetManagerNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->type = type;
    p->memberIds = memberIds;
    return p;
}

const MessageContentPrototype* GroupSetManagerNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string GroupSetManagerNotificationContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    if (type == "1") {
        result += " set";
    } else {
        result += " cancel";
    }
    
    for (std::list<std::string>::const_iterator it = memberIds.begin(); it != memberIds.end(); ++it) {
        result += " ";
        result += getGroupNotificationUserName(*it);
    }
    
    if (type == "1") {
        result += " as group manager";
    } else {
		result += " group manager";
    }
    
    return result;
}

std::string GroupSetManagerNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}
};
