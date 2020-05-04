//
//  UnknownMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "UnknownMessageContent.h"

namespace WFCLib {

MessageContent* UnknownMessageContent::clone() const {
    UnknownMessageContent *p = new UnknownMessageContent();
    p->rawPayload = rawPayload;
    return p;
}

std::string UnknownMessageContent::digest() const {
    return "未知消息类型";
}

MessageContent* UnknownMessageContentPrototype::productEmptyContent() const {
    return new UnknownMessageContent();
}
};
