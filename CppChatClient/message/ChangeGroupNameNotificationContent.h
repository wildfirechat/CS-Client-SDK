//
//  ChangeGroupNameNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ChangeGroupNameNotificationContent_hpp
#define ChangeGroupNameNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class ChangeGroupNameNotificationContentPrototype;
class ChangeGroupNameNotificationContent : public NotificationMessageContent
{
public:
    ChangeGroupNameNotificationContent() {}
    virtual ~ChangeGroupNameNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    //new name
    std::string name;
    static ChangeGroupNameNotificationContentPrototype sPrototype;
};

class ChangeGroupNameNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_CHANGE_GROUP_NAME; }
    virtual MessageContent *productEmptyContent() const { return new ChangeGroupNameNotificationContent(); }
};
};
#endif /* ChangeGroupNameNotificationContent_hpp */
