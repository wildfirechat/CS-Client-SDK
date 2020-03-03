//
//  NotificationMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef NotificationMessageContent_hpp
#define NotificationMessageContent_hpp

#include "MessageContent.h"

namespace WFCLib {

class Message;
class NotificationMessageContent : public MessageContent
{
public:
    NotificationMessageContent() {};
    virtual ~NotificationMessageContent() {};
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    //通知消息一般都是小灰条，使用这个函数来生成内容
    virtual std::string formatNotification(const Message &msg) const = 0;
    std::string getGroupNotificationUserName(const std::string &userId) const;
};
};
#endif /* NotificationMessageContent_hpp */
