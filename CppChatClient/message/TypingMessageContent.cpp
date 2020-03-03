//
//  TypingMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "TypingMessageContent.h"

namespace WFCLib {

TypingMessageContentPrototype TypingMessageContent::sPrototype;

MessagePayload TypingMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    payload.content = std::to_string(type);
    return payload;
}


void TypingMessageContent::decode(const MessagePayload & payload) {
    MessageContent::decode(payload);
    type = (TypingType)atoi(payload.content.c_str());
}

MessageContent* TypingMessageContent::clone() const {
    TypingMessageContent *p = new TypingMessageContent();
    p->extra = extra;
    p->type = type;
    return p;
}

const MessageContentPrototype* TypingMessageContent::getPrototype() const {
    return &sPrototype;
}


std::string TypingMessageContent::digest() const {
    switch (type) {
        case Typing_TEXT:
            return "正在输入文本...";
        case Typing_VOICE:
            return "正在录音...";
        case Typing_CAMERA:
            return "正在拍摄...";
        case Typing_LOCATION:
            return "正在选取位置...";
        case Typing_FILE:
            return "正在选取文件...";
        default:
            break;
    }
    return "正在输入...";
}
};
