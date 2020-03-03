//
//  Conversation.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "Conversation.h"
#include "../JsonTools.h"

namespace WFCLib {
void Conversation::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int conversationType;
    int i;
    getValue(value, "conversationType", i);
    conversationType = (ConversationType)i;
    
//            std::string target;
    getValue(value, "target", target);
//            int line;
    getValue(value, "line", line);
}

void Conversation::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

    writer.String("conversation");
    writer.StartObject();
//            int conversationType;
    writer.String("conversationType");
    writer.Int(conversationType);

//            std::string target;
    writer.String("target");
    writer.String(target);

    writer.EndObject();
}
};
