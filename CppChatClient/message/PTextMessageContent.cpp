//
//  PTextMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "PTextMessageContent.h"

namespace WFCLib {

PTextMessageContentPrototype PTextMessageContent::sPrototype;

MessagePayload PTextMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    payload.searchableContent = content;
    return payload;
}


void PTextMessageContent::decode(const MessagePayload & payload){
    MessageContent::decode(payload);
    content = payload.searchableContent;
}

MessageContent* PTextMessageContent::clone() const {
    PTextMessageContent *p = new PTextMessageContent();
    p->extra = extra;
    p->content = content;
    return p;
}

const MessageContentPrototype* PTextMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string PTextMessageContent::digest() const {
    return content;
}
};
