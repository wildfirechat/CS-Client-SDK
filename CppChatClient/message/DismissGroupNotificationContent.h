//
//  DismissGroupNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef DismissGroupNotificationContent_hpp
#define DismissGroupNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class DismissGroupNotificationContentPrototype;
class DismissGroupNotificationContent : public NotificationMessageContent
{
public:
    DismissGroupNotificationContent() {}
    virtual ~DismissGroupNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    static DismissGroupNotificationContentPrototype sPrototype;
};

class DismissGroupNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_DISMISS_GROUP; }
    virtual MessageContent *productEmptyContent() const { return new DismissGroupNotificationContent(); }
};
};
#endif /* DismissGroupNotificationContent_hpp */
