//
//  CreateGroupNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "CreateGroupNotificationContent.h"
#include "../JsonTools.h"

namespace WFCLib {

CreateGroupNotificationContentPrototype CreateGroupNotificationContent::sPrototype;

CreateGroupNotificationContent::CreateGroupNotificationContent()
{
}

MessagePayload CreateGroupNotificationContent::encode() const
{
    MessagePayload payload = NotificationMessageContent::encode();
    
    JsonBuilder builder;
    builder.setValue("g", groupId);
    builder.setValue("o", operatorId);
    builder.setValue("n", groupName);
    
    payload.binaryContent = builder.build();

    return payload;
}

MessageContent* CreateGroupNotificationContent::clone() const {
    CreateGroupNotificationContent *p = new CreateGroupNotificationContent();
    p->extra = extra;
    p->groupId = groupId;
    p->operatorId = operatorId;
    p->groupName = groupName;
    return p;
}

const MessageContentPrototype* CreateGroupNotificationContent::getPrototype() const {
    return &sPrototype;
}

void CreateGroupNotificationContent::decode(const MessagePayload & payload)
{
    NotificationMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    
    parser.getValue("o", operatorId);
    parser.getValue("g", groupId);
    parser.getValue("n", groupName);
}

std::string CreateGroupNotificationContent::digest() const {
    return getGroupNotificationUserName(operatorId) + " create group";
}

std::string CreateGroupNotificationContent::formatNotification(const Message &msg) const {
    return digest();
}

CreateGroupNotificationContent::~CreateGroupNotificationContent()
{
}

MessageContentType CreateGroupNotificationContentPrototype::getType() const
{
    return MESSAGE_CONTENT_TYPE_CREATE_GROUP;
}

MessageContentPersistFlag CreateGroupNotificationContentPrototype::getFlag() const
{
    return PersistFlag_PERSIST;
}

MessageContent * CreateGroupNotificationContentPrototype::productEmptyContent() const
{
    return new CreateGroupNotificationContent();
}
};
