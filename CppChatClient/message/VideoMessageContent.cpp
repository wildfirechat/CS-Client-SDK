//
//  VideoMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "VideoMessageContent.h"

namespace WFCLib {

VideoMessageContentPrototype VideoMessageContent::sPrototype;

MessagePayload VideoMessageContent::encode() const {
    MessagePayload payload = MediaMessageContent::encode();
    payload.binaryContent = thumbnail;
    return payload;
}

void VideoMessageContent::decode(const MessagePayload & payload) {
    MediaMessageContent::decode(payload);
    thumbnail = payload.binaryContent;
}

MessageContent* VideoMessageContent::clone() const {
    VideoMessageContent *p = new VideoMessageContent();
    p->extra = extra;
    p->thumbnail = thumbnail;
    p->localPath = localPath;
    p->remoteUrl = remoteUrl;
    return p;
}

const MessageContentPrototype* VideoMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string VideoMessageContent::digest() const {
    return "[视频]";
}
};
