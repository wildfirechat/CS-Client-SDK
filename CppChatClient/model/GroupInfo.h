//
//  GroupInfo.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupInfo_hpp
#define GroupInfo_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {
class GroupInfo : public Serializable {
public:
    GroupInfo() : target(""), type(0), memberCount(0), updateDt(0), mute(0), joinType(0), privateChat(0), searchable(0) {}
    std::string target;
    std::string name;
    std::string portrait;
    std::string owner;
    int type;
    int memberCount;
    std::string extra;
    int64_t updateDt;
    int mute;
    int joinType;
    int privateChat;
    int searchable;
    virtual ~GroupInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};

class GroupMember : public Serializable {
public:
    GroupMember() : type(0), updateDt(0) {}
    std::string groupId;
    std::string memberId;
    std::string alias;
    int type;
    int64_t updateDt;
    virtual ~GroupMember() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* GroupInfo_hpp */
