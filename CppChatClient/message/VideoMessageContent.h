//
//  VideoMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef VideoMessageContent_hpp
#define VideoMessageContent_hpp

#include "MessageContent.h"
#include "MediaMessageContent.h"

namespace WFCLib {

class VideoMessageContentPrototype;
class VideoMessageContent : public MediaMessageContent
{
public:
    VideoMessageContent() {}
    virtual ~VideoMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual MediaType getMediaType() const { return Media_Type_VIDEO; }
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string thumbnail;
    
    static VideoMessageContentPrototype sPrototype;
};

class VideoMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_VIDEO; }
    virtual MessageContent *productEmptyContent() const { return new VideoMessageContent(); }
};
};
#endif /* VideoMessageContent_hpp */
