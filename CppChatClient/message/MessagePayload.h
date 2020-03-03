#pragma once
#include <string>
#include <list>
#include "../Serializable.h"

namespace WFCLib {
class MessagePayload : public Serializable
{
public:
	MessagePayload();
	virtual ~MessagePayload();

    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
public:
    int contentType;
	std::string searchableContent;
    std::string pushContent;
    std::string content;
    std::string binaryContent;
    std::string localContent;
    std::string remoteMediaUrl;
    std::string localMediaPath;
    int mediaType;
    int mentionedType;
    std::list<std::string> mentionedTargets;
    std::string extra;
};
};
