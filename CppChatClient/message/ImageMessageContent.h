//
//  ImageMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ImageMessageContent_hpp
#define ImageMessageContent_hpp

#include "MessageContent.h"
#include "MediaMessageContent.h"

namespace WFCLib {
class ImageMessageContentPrototype;
class ImageMessageContent : public MediaMessageContent
{
public:
    ImageMessageContent() {}
    virtual ~ImageMessageContent() {}
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual MediaType getMediaType() const { return Media_Type_IMAGE; }
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string thumbnail;
    
    static ImageMessageContentPrototype sPrototype;
};

class ImageMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_IMAGE; }
    virtual MessageContent *productEmptyContent() const { return new ImageMessageContent(); }
};
};
#endif /* ImageMessageContent_hpp */
