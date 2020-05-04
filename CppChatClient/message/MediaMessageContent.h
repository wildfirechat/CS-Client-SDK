//
//  MediaMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef MediaMessageContent_hpp
#define MediaMessageContent_hpp

#include <stdio.h>
#include "MessageContent.h"
#include "../WFEnums.h"

namespace WFCLib {
class MediaMessageContent : public MessageContent
{
public:
    MediaMessageContent() {};
    virtual ~MediaMessageContent() {};
    
    /*
     下面两个函数需要都在子类中实现！子类实现时需要调用基类函数
     */
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    virtual MediaType getMediaType() const = 0;
public:
    std::string localPath;
    std::string remoteUrl;
};

};
#endif /* MediaMessageContent_hpp */
