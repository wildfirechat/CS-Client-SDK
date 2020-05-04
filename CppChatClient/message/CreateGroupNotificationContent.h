//
//  CreateGroupNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef CreateGroupNotificationContent_hpp
#define CreateGroupNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class CreateGroupNotificationContentPrototype;
class CreateGroupNotificationContent : public NotificationMessageContent
{
public:
    CreateGroupNotificationContent();
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    virtual ~CreateGroupNotificationContent();
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    std::string groupName;
    static CreateGroupNotificationContentPrototype sPrototype;
};

class CreateGroupNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const;
    virtual MessageContentType getType() const;
    virtual MessageContent *productEmptyContent() const;
};
};
#endif /* CreateGroupNotificationContent_hpp */
