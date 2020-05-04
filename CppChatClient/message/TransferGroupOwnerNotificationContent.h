//
//  TransferGroupOwnerNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef TransferGroupOwnerNotificationContent_hpp
#define TransferGroupOwnerNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class TransferGroupOwnerNotificationContentPrototype;
class TransferGroupOwnerNotificationContent : public NotificationMessageContent
{
public:
    TransferGroupOwnerNotificationContent() {}
    virtual ~TransferGroupOwnerNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    //new owner
    std::string owner;
    static TransferGroupOwnerNotificationContentPrototype sPrototype;
};

class TransferGroupOwnerNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_TRANSFER_GROUP_OWNER; }
    virtual MessageContent *productEmptyContent() const { return new TransferGroupOwnerNotificationContent(); }
};
};
#endif /* TransferGroupOwnerNotificationContent_hpp */
