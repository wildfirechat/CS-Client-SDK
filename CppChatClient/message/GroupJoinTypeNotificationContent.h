//
//  GroupJoinTypeNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupJoinTypeNotificationContent_hpp
#define GroupJoinTypeNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class GroupJoinTypeNotificationContentPrototype;
class GroupJoinTypeNotificationContent : public NotificationMessageContent
{
public:
    GroupJoinTypeNotificationContent() {}
    virtual ~GroupJoinTypeNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    
    //运行加入状态。“0”运行所有人加入，“1”只运行群成员邀请入群，“2”只允许群主或管理员邀请入群
    std::string type;
    static GroupJoinTypeNotificationContentPrototype sPrototype;
};

class GroupJoinTypeNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_CHANGE_JOINTYPE; }
    virtual MessageContent *productEmptyContent() const { return new GroupJoinTypeNotificationContent(); }
};
};
#endif /* GroupJoinTypeNotificationContent_hpp */
