//
//  QuitGroupNotificationContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef QuitGroupNotificationContent_hpp
#define QuitGroupNotificationContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {
class QuitGroupNotificationContentPrototype;
class QuitGroupNotificationContent : public NotificationMessageContent
{
public:
    QuitGroupNotificationContent() {}
    virtual ~QuitGroupNotificationContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    static QuitGroupNotificationContentPrototype sPrototype;
};

class QuitGroupNotificationContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_QUIT_GROUP; }
    virtual MessageContent *productEmptyContent() const { return new QuitGroupNotificationContent(); }
};
};
#endif /* QuitGroupNotificationContent_hpp */
