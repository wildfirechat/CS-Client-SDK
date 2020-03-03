//
//  ChatroomInfo.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ChatroomInfo_hpp
#define ChatroomInfo_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {
class ChatroomInfo : public Serializable {
public:
    ChatroomInfo()  : title(""), desc(""), portrait(""), memberCount(0), createDt(0), updateDt(0), extra(""), state(0) {}
    std::string title;
    std::string desc;
    std::string portrait;
    int memberCount;
    int64_t createDt;
    int64_t updateDt;
    std::string extra;
    //0 normal; 1 not started; 2 end
    int state;
    virtual ~ChatroomInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
};

class ChatroomMemberInfo : public Serializable {
public:
    ChatroomMemberInfo()  : memberCount(0) {}
    int memberCount;
    std::list<std::string> olderMembers;
    virtual ~ChatroomMemberInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
};
};
#endif /* ChatroomInfo_hpp */
