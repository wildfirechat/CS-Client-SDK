#pragma once
#include "MessageContent.h"

namespace WFCLib {
class TextMessageContentPrototype;
class TextMessageContent : public MessageContent
{
public:
    TextMessageContent() : mentionedType(0) {};
    virtual ~TextMessageContent() {};
    
	virtual MessagePayload encode() const;
	virtual void decode(const MessagePayload &payload);
	
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
	std::string content;
    /**
    提醒类型，1，提醒部分对象（mentinedTarget）。2，提醒全部。其他不提醒
    */
    int mentionedType;
    
    /**
    提醒对象，mentionedType 1时有效
    */
    std::list<std::string> mentionedTargets;
    static TextMessageContentPrototype sPrototype;
};

class TextMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_TEXT; }
    virtual MessageContent *productEmptyContent() const { return new TextMessageContent(); }
};

};
