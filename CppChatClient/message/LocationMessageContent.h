//
//  LocationMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef LocationMessageContent_hpp
#define LocationMessageContent_hpp

#include "MessageContent.h"

namespace WFCLib {

class LocationMessageContentPrototype;
class LocationMessageContent : public MessageContent
{
public:
    LocationMessageContent() : latitude(0), longitude(0) {}
    virtual ~LocationMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    double latitude;
    double longitude;
    std::string title;
    std::string thumbnail;
    
    static LocationMessageContentPrototype sPrototype;
};

class LocationMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_LOCATION; }
    virtual MessageContent *productEmptyContent() const { return new LocationMessageContent(); }
};
};
#endif /* LocationMessageContent_hpp */
