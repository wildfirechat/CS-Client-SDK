//
//  ChannelInfo.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ChannelInfo_hpp
#define ChannelInfo_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {
class ChannelInfo : public Serializable {
public:
    ChannelInfo() : status(0), updateDt(0), automatic(0) {}
    std::string channelId;
    std::string name;
    std::string portrait;
    std::string owner;
    int status;
    std::string desc;
    std::string extra;
    std::string secret;
    std::string callback;
    int64_t updateDt;
    int automatic;
    virtual ~ChannelInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* ChannelInfo_hpp */
