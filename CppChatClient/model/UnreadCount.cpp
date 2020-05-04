//
//  UnreadCount.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "UnreadCount.h"
#include "../JsonTools.h"

namespace WFCLib {
void UnreadCount::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int unread;
    getValue(value, "unread", unread);
//            int unreadMention;
    getValue(value, "unreadMention", unreadMention);
//            int unreadMentionAll;
    getValue(value, "unreadMentionAll", unreadMentionAll);
}

void UnreadCount::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

    writer.String("unread");
    writer.Int(unread);
    writer.String("unreadMention");
    writer.Int(unreadMention);
    writer.String("unreadMentionAll");
    writer.Int(unreadMentionAll);

    writer.EndObject();
}
};
