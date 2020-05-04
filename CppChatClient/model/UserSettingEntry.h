//
//  UserSettingEntry.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef UserSettingEntry_hpp
#define UserSettingEntry_hpp

#include <stdio.h>
#include "../Serializable.h"
#include "../WFEnums.h"


namespace WFCLib {
class UserSettingEntry : public Serializable {
public:
    UserSettingEntry() : scope(kUserSettingCustomBegin), updateDt(0) {}
    UserSettingScope scope;
    std::string key;
    std::string value;
    int64_t updateDt;
    virtual ~UserSettingEntry(){}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* UserSettingEntry_hpp */
