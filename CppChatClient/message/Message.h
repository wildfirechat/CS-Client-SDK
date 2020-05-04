//
//  Message.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

#include <stdio.h>
#include "../Serializable.h"
#include "MessagePayload.h"
#include "../model/Conversation.h"
#include "MessageContent.h"

namespace WFCLib {
typedef enum {
    Message_Status_Sending,
    Message_Status_Sent,
    Message_Status_Send_Failure,
    Message_Status_Mentioned,
    Message_Status_AllMentioned,
    Message_Status_Unread,
    Message_Status_Readed,
    Message_Status_Played
} MessageStatus;

class Message : public Serializable {
public:
    Message() : conversation(), content(NULL), messageId(-1), direction(Direction_Send), status(Message_Status_Sending), messageUid(0), timestamp(0) {}
    virtual ~Message() {if(content){delete content; content = NULL;}}
    Message(const Message &m);
    
    Conversation conversation;
    
    std::string from;
    MessageContent *content;
    long messageId;
    MessageDirection direction;
    MessageStatus status;
    int64_t messageUid;
    int64_t timestamp;
    std::list<std::string> to;

    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
};

};
#endif /* Message_hpp */
