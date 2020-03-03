//
//  LocationMessageContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "LocationMessageContent.h"
#include "../JsonTools.h"

namespace WFCLib {

LocationMessageContentPrototype LocationMessageContent::sPrototype;

MessagePayload LocationMessageContent::encode() const {
    MessagePayload payload = MessageContent::encode();
    payload.searchableContent = title;
    payload.binaryContent = thumbnail;
    
    JsonBuilder builder;
    builder.setValue("lat", latitude);
    builder.setValue("long", longitude);
    payload.content = builder.build();
    
    return payload;
}

void LocationMessageContent::decode(const MessagePayload & payload) {
    MessageContent::decode(payload);
    
    title = payload.searchableContent;
    thumbnail = payload.binaryContent;
    
    JsonParser parser(payload.content);
    if (!parser.isParsed()) {
        return;
    }
    parser.getValue("lat", latitude);
    parser.getValue("long", longitude);
}

MessageContent* LocationMessageContent::clone() const {
    LocationMessageContent *p = new LocationMessageContent();
    p->extra = extra;

    return p;
}

const MessageContentPrototype* LocationMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string LocationMessageContent::digest() const {
    return "[位置]";
}
};
