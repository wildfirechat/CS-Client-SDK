//
//  TypingMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef TypingMessageContent_hpp
#define TypingMessageContent_hpp

#include "MessageContent.h"
#include "../WFEnums.h"

namespace WFCLib {

class TypingMessageContentPrototype;
class TypingMessageContent : public MessageContent
{
public:
    TypingMessageContent() : type(Typing_TEXT) {}
    virtual ~TypingMessageContent() {}
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    TypingType type;
    static TypingMessageContentPrototype sPrototype;
};

class TypingMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_TRANSPARENT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_TYPING; }
    virtual MessageContent *productEmptyContent() const { return new TypingMessageContent(); }
};
};
#endif /* TypingMessageContent_hpp */
