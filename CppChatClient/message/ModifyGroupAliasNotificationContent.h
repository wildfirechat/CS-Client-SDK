//
//  ModifyGroupAliasNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ModifyGroupAliasNotificationContent_hpp
#define ModifyGroupAliasNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class ModifyGroupAliasNotificationContentPrototype;
class ModifyGroupAliasNotificationContent : public NotificationMessageContent
{
public:
    ModifyGroupAliasNotificationContent() {}
    virtual ~ModifyGroupAliasNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    //new alias
    std::string alias;
    static ModifyGroupAliasNotificationContentPrototype sPrototype;
};

class ModifyGroupAliasNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_MODIFY_GROUP_ALIAS; }
    virtual MessageContent *productEmptyContent() const { return new ModifyGroupAliasNotificationContent(); }
};
};
#endif /* ModifyGroupAliasNotificationContent_hpp */
