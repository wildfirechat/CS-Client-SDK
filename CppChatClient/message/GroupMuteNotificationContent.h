//
//  GroupMuteNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupMuteNotificationContent_hpp
#define GroupMuteNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class GroupMuteNotificationContentPrototype;
class GroupMuteNotificationContent : public NotificationMessageContent
{
public:
    GroupMuteNotificationContent() {}
    virtual ~GroupMuteNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    
    //禁言状态，“0”不禁言，“1”禁言
    std::string type;
    
    static GroupMuteNotificationContentPrototype sPrototype;
};

class GroupMuteNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_CHANGE_MUTE; }
    virtual MessageContent *productEmptyContent() const { return new GroupMuteNotificationContent(); }
};
};
#endif /* GroupMuteNotificationContent_hpp */
