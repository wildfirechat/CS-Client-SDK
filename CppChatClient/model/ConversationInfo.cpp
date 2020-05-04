//
//  ConversationInfo.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ConversationInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {

void ConversationInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

    int conversationType;
    getValue(value, "conversationType", conversationType);
    std::string target;
    getValue(value, "target", target);
    int line;
    getValue(value, "line", line);
    
    conversation.conversationType = (ConversationType)conversationType;
    conversation.target = target;
    conversation.line = line;
    
//            TMessage lastMessage;
    getValue(value, "lastMessage", lastMessage);
//            int64_t timestamp;
    getValue(value, "timestamp", timestamp);
//            std::string draft;
    getValue(value, "draft", draft);
//            TUnreadCount unreadCount;
    getValue(value, "unreadCount", unreadCount);
//            bool isTop;
    getValue(value, "isTop", isTop);
//            bool isSilent;
    getValue(value, "isSilent", isSilent);
}

void ConversationInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            int conversationType;
    writer.String("conversationType");
    writer.Int(conversation.conversationType);
//            std::string target;
    writer.String("target");
    writer.String(conversation.target);
//            int line;
    writer.String("line");
    writer.Int(conversation.line);
//            TMessage lastMessage;
    writer.String("lastMessage");
    lastMessage.Serialize(pwriter);
//            int64_t timestamp;
    writer.String("timestamp");
    writer.Int64(timestamp);
//            std::string draft;
    writer.String("draft");
    writer.String(draft);
//            TUnreadCount unreadCount;
    writer.String("unreadCount");
    unreadCount.Serialize(pwriter);
//            bool isTop;
    writer.String("isTop");
    writer.Bool(isTop);
//            bool isSilent;
    writer.String("isSilent");
    writer.Bool(isSilent);

    writer.EndObject();
}

};
