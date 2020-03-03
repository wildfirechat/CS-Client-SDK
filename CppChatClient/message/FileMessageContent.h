//
//  FileMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef FileMessageContent_hpp
#define FileMessageContent_hpp

#include "MessageContent.h"
#include "MediaMessageContent.h"

namespace WFCLib {

class FileMessageContentPrototype;
class FileMessageContent : public MediaMessageContent
{
public:
    FileMessageContent() : size(0) {}
    virtual ~FileMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual MediaType getMediaType() const { return Media_Type_File; }
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string name;
    long size;
    static FileMessageContentPrototype sPrototype;
};

class FileMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_FILE; }
    virtual MessageContent *productEmptyContent() const { return new FileMessageContent(); }
};
};
#endif /* FileMessageContent_hpp */
