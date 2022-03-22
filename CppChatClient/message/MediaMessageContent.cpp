//
//  MediaMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "MediaMessageContent.h"

namespace WFCLib {

MessagePayload MediaMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    payload.localMediaPath = localPath;
    payload.remoteMediaUrl = remoteUrl;
    payload.mediaType = getMediaType();
    return payload;
}

void MediaMessageContent::decode(const MessagePayload &payload) {
    MessageContent::decode(payload);
    localPath = payload.localMediaPath;
    remoteUrl = payload.remoteMediaUrl;
}
};
