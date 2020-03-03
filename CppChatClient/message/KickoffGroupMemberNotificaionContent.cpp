//
//  KickoffGroupMemberNotificaionContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "KickoffGroupMemberNotificaionContent.h"
#include "../JsonTools.h"

namespace WFCLib {

KickoffGroupMemberNotificaionContentPrototype KickoffGroupMemberNotificaionContent::sPrototype;

MessagePayload KickoffGroupMemberNotificaionContent::encode() const {
    MessagePayload payload = NotificationMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("g", groupId);
    builder.setValue("o", operatorId);
    builder.setValue("ms", kickedMembers);
    
    payload.binaryContent = builder.build();

    return payload;
}

void KickoffGroupMemberNotificaionContent::decode(const MessagePayload & payload) {
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("ms", kickedMembers);
}

MessageContent* KickoffGroupMemberNotificaionContent::clone() const {
    KickoffGroupMemberNotificaionContent *p = new KickoffGroupMemberNotificaionContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->kickedMembers = kickedMembers;
    return p;
}

const MessageContentPrototype* KickoffGroupMemberNotificaionContent::getPrototype() const {
    return &sPrototype;
}


std::string KickoffGroupMemberNotificaionContent::digest() const {
    std::string result = getGroupNotificationUserName(operatorId);
    
    result += " 把 ";
    for (std::list<std::string>::const_iterator it = kickedMembers.begin(); it != kickedMembers.end(); ++it) {
        const std::string &userId = *it;
        result += " ";
        result += getGroupNotificationUserName(userId);
    }
    result += " 移出群组";
    
    return result;
}

std::string KickoffGroupMemberNotificaionContent::formatNotification(const Message &msg) const {
    return digest();
}
};
