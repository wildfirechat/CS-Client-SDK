//
//  ConversationSearchresult.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ConversationSearchInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {
void ConversationSearchInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int conversationType;
    getValue(value, "conversationType", conversationType);
//            std::string target;
    getValue(value, "target", target);
//            int line;
    getValue(value, "line", line);
//            //only marchedCount == 1, load the message
//            TMessage marchedMessage;
    getValue(value, "marchedMessage", marchedMessage);
//            int64_t timestamp;
    getValue(value, "timestamp", timestamp);
//            int marchedCount;
    getValue(value, "marchedCount", marchedCount);
}

void ConversationSearchInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            int conversationType;
    writer.String("conversationType");
    writer.Int(conversationType);
//            std::string target;
    writer.String("target");
    writer.String(target);
//            int line;
    writer.String("line");
    writer.Int(line);
//            //only marchedCount == 1, load the message
//            TMessage marchedMessage;
    writer.String("marchedMessage");
    marchedMessage.Serialize(&writer);
//            int64_t timestamp;
    writer.String("timestamp");
    writer.Int64(timestamp);
//            int marchedCount;
    writer.String("marchedCount");
    writer.Int(marchedCount);
    writer.EndObject();
}
};
