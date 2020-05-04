//
//  ChatroomInfo.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ChatroomInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {
void ChatroomInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }
//            std::string title;
    getValue(value, "title", title);
//            std::string desc;
    getValue(value, "desc", desc);
//            std::string portrait;
    getValue(value, "portrait", portrait);
//            int memberCount;
    getValue(value, "memberCount", memberCount);
//            int64_t createDt;
    getValue(value, "createDt", createDt);
//            int64_t updateDt;
    getValue(value, "updateDt", updateDt);
//            std::string extra;
    getValue(value, "extra", extra);

    
//            //0 normal; 1 not started; 2 end
//            int state;
    getValue(value, "state", state);
}

void ChatroomInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            std::string title;
    writer.String("title");
    writer.String(title);
//            std::string desc;
    writer.String("desc");
    writer.String(desc);
//            std::string portrait;
    writer.String("portrait");
    writer.String(portrait);
//            int memberCount;
    writer.String("memberCount");
    writer.Int(memberCount);
//            int64_t createDt;
    writer.String("createDt");
    writer.Int64(createDt);
//            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);
//            std::string extra;
    writer.String("extra");
    writer.String(extra);
//            //0 normal; 1 not started; 2 end
//            int state;
    writer.String("state");
    writer.Int(state);

    writer.EndObject();
}

void ChatroomMemberInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int memberCount;
    getValue(value, "memberCount", memberCount);
//            std::list<std::string> olderMembers;
    getValue(value, "olderMembers", olderMembers);
}

void ChatroomMemberInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            int memberCount;
//            std::list<std::string> olderMembers;

    writer.EndObject();
}
};
