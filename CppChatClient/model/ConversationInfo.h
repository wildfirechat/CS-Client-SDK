//
//  ConversationInfo.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ConversationInfo_hpp
#define ConversationInfo_hpp

#include <stdio.h>
#include "../Serializable.h"
#include "../message/Message.h"
#include "Conversation.h"
#include "UnreadCount.h"

namespace WFCLib {
class ConversationInfo : public Serializable {
public:
    ConversationInfo() : conversation(), lastMessage() , timestamp(0), unreadCount(), isTop(false), isSilent(false) {}
    Conversation conversation;
    Message lastMessage;
    int64_t timestamp;
    std::string draft;
    UnreadCount unreadCount;
    int isTop;
    bool isSilent;
    virtual ~ConversationInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
};
};
#endif /* ConversationInfo_hpp */
