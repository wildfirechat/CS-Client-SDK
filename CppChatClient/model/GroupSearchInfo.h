//
//  GroupSearchResult.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef GroupSearchResult_hpp
#define GroupSearchResult_hpp

#include <stdio.h>
#include "../Serializable.h"
#include "GroupInfo.h"

namespace WFCLib {
class GroupSearchInfo : public Serializable {
public:
    GroupSearchInfo() : marchedType(-1)  {}
    GroupInfo groupInfo;
    int marchedType;  //0 march name, 1 march group member, 2 both
    std::list<std::string> marchedMemberNames;
    virtual ~GroupSearchInfo(){}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* GroupSearchResult_hpp */
