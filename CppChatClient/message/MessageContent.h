#pragma once
#include "MessagePayload.h"
#include <string>
#include "../WFEnums.h"

namespace WFCLib {
class MessageContentPrototype;
class MessageContent
{
public:
    MessageContent() {};
    virtual ~MessageContent() {};
    
    //具体消息内容类必须要实现
	virtual MessagePayload encode() const;
    
    //具体消息内容类必须要实现
	virtual void decode(const MessagePayload &payload);
	
    //克隆一个新的消息内容实体类，需要注意避免忘记克隆基类的属性
    virtual MessageContent* clone() const = 0;
    
    //消息内容摘要函数，用来方便UI显示消息摘要信息
    virtual std::string digest() const = 0;
    
    //消息内容类原形
    virtual const MessageContentPrototype* getPrototype() const = 0;
public:
    std::string extra;
};

class MessageContentPrototype
{
public:
	MessageContentPrototype() {}
	virtual MessageContentType getType() const = 0;
	virtual MessageContentPersistFlag getFlag() const = 0;
	virtual MessageContent *productEmptyContent() const = 0;
	virtual ~MessageContentPrototype() {}
};

};
