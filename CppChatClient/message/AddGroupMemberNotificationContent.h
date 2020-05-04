//
//  AddGroupMemberNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef AddGroupMemberNotificationContent_hpp
#define AddGroupMemberNotificationContent_hpp

#include "NotificationMessageContent.h"

namespace WFCLib {

class AddGroupMemberNotificationContentPrototype;
class AddGroupMemberNotificationContent : public NotificationMessageContent
{
public:
    AddGroupMemberNotificationContent();
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    virtual ~AddGroupMemberNotificationContent();
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    std::list<std::string> invitees;
    static AddGroupMemberNotificationContentPrototype sPrototype;
};

class AddGroupMemberNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const;
    virtual MessageContentType getType() const;
    virtual MessageContent *productEmptyContent() const;
};
};
#endif /* AddGroupMemberNotificationContent_hpp */
