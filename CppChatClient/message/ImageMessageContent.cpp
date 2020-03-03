//
//  ImageMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ImageMessageContent.h"

namespace WFCLib {

ImageMessageContentPrototype ImageMessageContent::sPrototype;

MessagePayload ImageMessageContent::encode() const {
    MessagePayload payload = MediaMessageContent::encode();
    payload.binaryContent = thumbnail;
    return payload;
}

void ImageMessageContent::decode(const MessagePayload & payload) {
    MediaMessageContent::decode(payload);
    thumbnail = payload.binaryContent;
}

MessageContent* ImageMessageContent::clone() const {
    ImageMessageContent *p = new ImageMessageContent();
    p->extra = extra;
    p->thumbnail = thumbnail;
    p->localPath = localPath;
    p->remoteUrl = remoteUrl;
    return p;
}

const MessageContentPrototype* ImageMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string ImageMessageContent::digest() const {
    return "[图片]";
}

};
