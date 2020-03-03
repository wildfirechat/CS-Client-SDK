//
//  StickerMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef StickerMessageContent_hpp
#define StickerMessageContent_hpp

#include "MessageContent.h"
#include "MediaMessageContent.h"

namespace WFCLib {

class StickerMessageContentPrototype;
class StickerMessageContent : public MediaMessageContent
{
public:
    StickerMessageContent() : width(0), height(0) {}
    virtual ~StickerMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual MediaType getMediaType() const { return Media_Type_IMAGE; }
    virtual const MessageContentPrototype* getPrototype() const;
public:
    int width;
    int height;
    static StickerMessageContentPrototype sPrototype;
};

class StickerMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_STICKER; }
    virtual MessageContent *productEmptyContent() const { return new StickerMessageContent(); }
};
};
#endif /* StickerMessageContent_hpp */
