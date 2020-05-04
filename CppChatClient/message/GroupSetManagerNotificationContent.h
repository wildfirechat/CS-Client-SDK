//
//  GroupSetManagerNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupSetManagerNotificationContent_hpp
#define GroupSetManagerNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class GroupSetManagerNotificationContentPrototype;
class GroupSetManagerNotificationContent : public NotificationMessageContent
{
public:
    GroupSetManagerNotificationContent() {}
    virtual ~GroupSetManagerNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    //操作类型，“0”取消管理员，“1”设置管理员
    std::string type;
    std::list<std::string> memberIds;
    
    static GroupSetManagerNotificationContentPrototype sPrototype;
};

class GroupSetManagerNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_SET_MANAGER; }
    virtual MessageContent *productEmptyContent() const { return new GroupSetManagerNotificationContent(); }
};
};
#endif /* GroupSetManagerNotificationContent_hpp */
