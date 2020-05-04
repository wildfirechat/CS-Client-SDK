//
//  GroupPrivateChatNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupPrivateChatNotificationContent_hpp
#define GroupPrivateChatNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class GroupPrivateChatNotificationContentPrototype;
class GroupPrivateChatNotificationContent : public NotificationMessageContent
{
public:
    GroupPrivateChatNotificationContent() {}
    virtual ~GroupPrivateChatNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    
    //禁止私聊状态，“0”不禁止私聊，“1”禁止私聊
    std::string type;
    static GroupPrivateChatNotificationContentPrototype sPrototype;
};

class GroupPrivateChatNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_CHANGE_PRIVATECHAT; }
    virtual MessageContent *productEmptyContent() const { return new GroupPrivateChatNotificationContent(); }
};
};
#endif /* GroupPrivateChatNotificationContent_hpp */
