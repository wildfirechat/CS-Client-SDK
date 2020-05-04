//
//  TipNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef TipNotificationContent_hpp
#define TipNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {

class TipNotificationContentPrototype;
class TipNotificationContent : public NotificationMessageContent
{
public:
    TipNotificationContent() {}
    virtual ~TipNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string tip;
    static TipNotificationContentPrototype sPrototype;
};

class TipNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_TIP; }
    virtual MessageContent *productEmptyContent() const { return new TipNotificationContent(); }
};
};
#endif /* TipNotificationContent_hpp */
