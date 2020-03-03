//
//  FileMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "FileMessageContent.h"
#include <sstream>
#include <stdlib.h>

namespace WFCLib {

FileMessageContentPrototype FileMessageContent::sPrototype;

MessagePayload FileMessageContent::encode() const {
    MessagePayload payload = MediaMessageContent::encode();
    
    std::stringstream sstream;
    sstream << size;
    sstream >> payload.content;
    payload.searchableContent = name;
    
    return payload;
}

void FileMessageContent::decode(const MessagePayload & payload) {
    MediaMessageContent::decode(payload);
    size = atol(payload.content.c_str());
    name = payload.searchableContent;
}

MessageContent* FileMessageContent::clone() const {
    FileMessageContent *p = new FileMessageContent();
    p->extra = extra;
    p->name = name;
    p->size = size;
    p->localPath = localPath;
    p->remoteUrl = remoteUrl;
    return p;
}

const MessageContentPrototype* FileMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string FileMessageContent::digest() const {
    return "[文件]" + name;
}
};
