//
//  RecallMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "RecallMessageContent.h"

namespace WFCLib {

RecallMessageContentPrototype RecallMessageContent::sPrototype;

MessagePayload RecallMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    payload.content = operatorId;
    payload.binaryContent = std::to_string(messageUid);
    return payload;
}

void RecallMessageContent::decode(const MessagePayload & payload) {
    MessageContent::decode(payload);
    operatorId = payload.content;
    messageUid = atoll(payload.binaryContent.c_str());
}

MessageContent* RecallMessageContent::clone() const {
    RecallMessageContent *p = new RecallMessageContent();
    p->extra = extra;
    p->operatorId = operatorId;
    p->messageUid = messageUid;
    return p;
}

const MessageContentPrototype* RecallMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string RecallMessageContent::digest() const {
	return "Recall a message";
}
};
