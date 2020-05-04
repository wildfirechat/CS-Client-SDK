//
//  GroupSearchResult.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "GroupSearchInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {

void GroupSearchInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            TGroupInfo groupInfo;
    getValue(value, "groupInfo", groupInfo);
//            int marchedType;  //0 march name, 1 march group member, 2 both
    getValue(value, "marchedType", marchedType);
//            std::list<std::string> marchedMemberNames;
    getValue(value, "marchedMemberNames", marchedMemberNames);
}

void GroupSearchInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            TGroupInfo groupInfo;
    writer.String("groupInfo");
    groupInfo.Serialize(&writer);

//            int marchedType;  //0 march name, 1 march group member, 2 both
    writer.String("marchedType");
    writer.Int(marchedType);
//            std::list<std::string> marchedMemberNames;
    writer.String("marchedMemberNames");
    writer.StartArray();
    for (std::list<std::string>::const_iterator it = marchedMemberNames.begin(); it != marchedMemberNames.end(); ++it) {
        writer.String(*it);
    }
    writer.EndArray();

    writer.EndObject();
}
};
