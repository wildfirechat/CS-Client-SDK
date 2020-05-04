#include "TextMessageContent.h"

namespace WFCLib {

TextMessageContentPrototype TextMessageContent::sPrototype;

MessagePayload TextMessageContent::encode() const
{
	MessagePayload payload = MessageContent::encode();
    
	payload.searchableContent = content;
    payload.mentionedType = mentionedType;
    payload.mentionedTargets = mentionedTargets;
    
	return payload;
}

void TextMessageContent::decode(const MessagePayload & payload)
{
    MessageContent::decode(payload);
    content = payload.searchableContent;
    mentionedType = payload.mentionedType;
    mentionedTargets = payload.mentionedTargets;
}

MessageContent* TextMessageContent::clone() const {
    TextMessageContent *p = new TextMessageContent();
    p->extra = extra;
    p->content = content;
    p->mentionedType = mentionedType;
    p->mentionedTargets = mentionedTargets;
    return p;
}

const MessageContentPrototype* TextMessageContent::getPrototype() const {
    return &sPrototype;
}

std::string TextMessageContent::digest() const {
    return content;
}

};
