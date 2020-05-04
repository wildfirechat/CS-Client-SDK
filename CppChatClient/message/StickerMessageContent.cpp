//
//  StickerMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "StickerMessageContent.h"
#include "../JsonTools.h"

namespace WFCLib {

StickerMessageContentPrototype StickerMessageContent::sPrototype;

MessagePayload StickerMessageContent::encode() const {
    MessagePayload payload = MediaMessageContent::encode();

    JsonBuilder builder;
    builder.setValue("x", width);
    builder.setValue("y", height);
    
    payload.binaryContent = builder.build();

    return payload;
}

void StickerMessageContent::decode(const MessagePayload & payload) {
    MediaMessageContent::decode(payload);
    JsonParser parser(payload.binaryContent);
    if (!parser.isParsed()) {
        return;
    }
    
    parser.getValue("x", width);
    parser.getValue("y", height);
}

MessageContent* StickerMessageContent::clone() const {
    StickerMessageContent *p = new StickerMessageContent();
    p->extra = extra;
    p->width = width;
    p->height = height;
    p->localPath = localPath;
    p->remoteUrl = remoteUrl;
    return p;
}

const MessageContentPrototype* StickerMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string StickerMessageContent::digest() const {
    return "[动态表情]";
}
};
