//
//  UserInfo.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef UserInfo_hpp
#define UserInfo_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {
class UserInfo : public Serializable {
public:
    UserInfo() : gender(0), type(0), deleted(0), updateDt(0) {}
    std::string uid;
    std::string name;
    std::string displayName;
    int gender;
    std::string portrait;
    std::string mobile;
    std::string email;
    std::string address;
    std::string company;
    std::string social;
    std::string extra;
    std::string friendAlias;
    std::string groupAlias;
    //0 normal; 1 robot; 2 thing;
    int type;
    int deleted;
    int64_t updateDt;
    virtual ~UserInfo() {}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* UserInfo_hpp */
