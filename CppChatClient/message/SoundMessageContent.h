//
//  SoundMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef SoundMessageContent_hpp
#define SoundMessageContent_hpp

#include "MessageContent.h"
#include "MediaMessageContent.h"

namespace WFCLib {
class SoundMessageContentPrototype;
class SoundMessageContent : public MediaMessageContent
{
public:
    SoundMessageContent() : duration(0) {}
    virtual ~SoundMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual MediaType getMediaType() const { return Media_Type_VOICE; }
    virtual const MessageContentPrototype* getPrototype() const;
public:
    long duration;
    static SoundMessageContentPrototype sPrototype;
};

class SoundMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_SOUND; }
    virtual MessageContent *productEmptyContent() const { return new SoundMessageContent(); }
};
};
#endif /* SoundMessageContent_hpp */
