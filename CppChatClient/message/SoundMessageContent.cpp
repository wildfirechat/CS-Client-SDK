//
//  SoundMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "SoundMessageContent.h"
#include "../JsonTools.h"

namespace WFCLib {

SoundMessageContentPrototype SoundMessageContent::sPrototype;

MessagePayload SoundMessageContent::encode() const {
    MessagePayload payload = MediaMessageContent::encode();
    JsonBuilder builder;
    builder.setValue("duration", duration);
    payload.content = builder.build();

    return payload;
}


void SoundMessageContent::decode(const MessagePayload & payload) {
    MediaMessageContent::decode(payload);
    JsonParser parser(payload.content);
    if (!parser.isParsed()) {
        return;
    }

    parser.getValue("duration", duration);
}


MessageContent* SoundMessageContent::clone() const {
    SoundMessageContent *p = new SoundMessageContent();
    p->extra = extra;
    p->duration = duration;
    p->localPath = localPath;
    p->remoteUrl = remoteUrl;
    return p;
}

const MessageContentPrototype* SoundMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string SoundMessageContent::digest() const {
    return "[语音]";
}
};
