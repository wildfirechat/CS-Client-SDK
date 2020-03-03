//
//  CallStartMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "CallStartMessageContent.h"
#include "../JsonTools.h"

namespace WFCLib {
CallStartMessageContentPrototype CallStartMessageContent::sPrototype;

MessagePayload CallStartMessageContent::encode() const
{
    MessagePayload payload = MessageContent::encode();
    payload.content = callId;

    JsonBuilder builder;
    
    builder.setValue("c", connectTime);
    builder.setValue("e", endTime);
    builder.setValue("s", status);
    builder.setValue("ts", targetIds);
    builder.setValue("a", audioOnly?1:0);
    
    payload.binaryContent = builder.build();
    
    return payload;
}

void CallStartMessageContent::decode(const MessagePayload & payload)
{
    MessageContent::decode(payload);
    
    JsonParser parser(payload.binaryContent);
    
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("c", connectTime);
    parser.getValue("e", endTime);
    parser.getValue("s", status);
    parser.getValue("ts", targetIds);
    int audio = 0;
    parser.getValue("a", audio);
    audioOnly = audio>0;
}

MessageContent* CallStartMessageContent::clone() const {
    CallStartMessageContent *p = new CallStartMessageContent();
    p->extra = extra;
    p->callId = callId;
    p->targetIds = targetIds;
    p->connectTime = connectTime;
    p->endTime = endTime;
    p->status = status;
    p->audioOnly = audioOnly;
    return p;
}

const MessageContentPrototype* CallStartMessageContent::getPrototype() const {
    return &sPrototype;
}

};

