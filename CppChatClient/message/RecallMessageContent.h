//
//  RecallMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef RecallMessageContent_hpp
#define RecallMessageContent_hpp

#include "MessageContent.h"

namespace WFCLib {

class RecallMessageContentPrototype;
class RecallMessageContent : public MessageContent
{
public:
    RecallMessageContent() : messageUid(0) {}
    virtual ~RecallMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    int64_t messageUid;
    std::string operatorId;
    
    static RecallMessageContentPrototype sPrototype;
};

class RecallMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_RECALL; }
    virtual MessageContent *productEmptyContent() const { return new RecallMessageContent(); }
};
};
#endif /* RecallMessageContent_hpp */
