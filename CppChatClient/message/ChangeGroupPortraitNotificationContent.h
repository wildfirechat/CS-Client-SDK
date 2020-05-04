//
//  ChangeGroupPortraitNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ChangeGroupPortraitNotificationContent_hpp
#define ChangeGroupPortraitNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class ChangeGroupPortraitNotificationContentPrototype;
class ChangeGroupPortraitNotificationContent : public NotificationMessageContent
{
public:
    ChangeGroupPortraitNotificationContent() {}
    virtual ~ChangeGroupPortraitNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    //new portrait
    std::string portrait;
    static ChangeGroupPortraitNotificationContentPrototype sPrototype;
};

class ChangeGroupPortraitNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_CHANGE_GROUP_PORTRAIT; }
    virtual MessageContent *productEmptyContent() const { return new ChangeGroupPortraitNotificationContent(); }
};
};
#endif /* ChangeGroupPortraitNotificationContent_hpp */
