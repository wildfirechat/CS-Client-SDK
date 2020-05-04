//
//  PTextMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef PTextMessageContent_hpp
#define PTextMessageContent_hpp

#include "MessageContent.h"

namespace WFCLib {

class PTextMessageContentPrototype;
class PTextMessageContent : public MessageContent
{
public:
    PTextMessageContent() {}
    virtual ~PTextMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string content;
    static PTextMessageContentPrototype sPrototype;
};

class PTextMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_P_TEXT; }
    virtual MessageContent *productEmptyContent() const { return new PTextMessageContent(); }
};
};
#endif /* PTextMessageContent_hpp */
