//
//  UnknownMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef UnknownMessageContent_hpp
#define UnknownMessageContent_hpp

#include <stdio.h>

#include "MessageContent.h"

namespace WFCLib {
class UnknownMessageContent;
class UnknownMessageContentPrototype : public MessageContentPrototype {
public:
    UnknownMessageContentPrototype() {}
    virtual ~UnknownMessageContentPrototype() {}
    UnknownMessageContent *content;
    virtual MessageContentPersistFlag getFlag() const { if(content) {
        return PersistFlag_NOT_PERSIST;
    } else {
        return PersistFlag_NOT_PERSIST;
    }}
    
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_UNKNOWN;}
    virtual MessageContent *productEmptyContent() const;
};

class UnknownMessageContent : public MessageContent
{
public:
    UnknownMessageContent() {}
    virtual ~UnknownMessageContent() {}
    
    
    virtual MessagePayload encode() const { return rawPayload; }
    virtual void decode(const MessagePayload &payload) { rawPayload = payload; prototype.content = this;}
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const { return &prototype; }
    
public:
    MessagePayload rawPayload;
    UnknownMessageContentPrototype prototype;
};

};
#endif /* UnknownMessageContent_hpp */
