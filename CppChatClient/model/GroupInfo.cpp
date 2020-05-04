//
//  GroupInfo.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "GroupInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {
void GroupInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }
    //            std::string target;
    getValue(value, "target", target);
    //            std::string name;
    getValue(value, "name", name);
    //            std::string portrait;
    getValue(value, "portrait", portrait);
    //            std::string owner;
    getValue(value, "owner", owner);
    //            int type;
    getValue(value, "type", type);
    //            int memberCount;
    getValue(value, "memberCount", memberCount);
    //            std::string extra;
    getValue(value, "extra", extra);
    //            int64_t updateDt;
    getValue(value, "updateDt", updateDt);

    getValue(value, "mute", mute);
    getValue(value, "joinType", joinType);
    getValue(value, "privateChat", privateChat);
    getValue(value, "searchable", searchable);
}

void GroupInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();
    //
    //            std::string target;
    writer.String("target");
    writer.String(target);
    //            std::string name;
    writer.String("name");
    writer.String(name);
    //            std::string portrait;
    writer.String("portrait");
    writer.String(portrait);
    //            std::string owner;
    writer.String("owner");
    writer.String(owner);
    //            int type;
    writer.String("type");
    writer.Int(type);
    //            int memberCount;
    writer.String("memberCount");
    writer.Int(memberCount);
    //            std::string extra;
    writer.String("extra");
    writer.String(extra);
    //            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);


    //            int mute;
    writer.String("mute");
    writer.Int(mute);

    //            int joinType;
    writer.String("joinType");
    writer.Int(joinType);

    //            int privateChat;
    writer.String("privateChat");
    writer.Int(privateChat);

    //            int searchable;
    writer.String("searchable");
    writer.Int(searchable);

    writer.EndObject();
}

void GroupMember::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }
    //            std::string groupId;
    getValue(value, "groupId", groupId);
    //            std::string memberId;
    getValue(value, "memberId", memberId);
    //            std::string alias;
    getValue(value, "alias", alias);
    //            int type;
    getValue(value, "type", type);
    //            int64_t updateDt;
    getValue(value, "updateDt", updateDt);
}

void GroupMember::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

    //            std::string groupId;
    writer.String("groupId");
    writer.String(groupId);
    //            std::string memberId;
    writer.String("memberId");
    writer.String(memberId);
    //            std::string alias;
    writer.String("alias");
    writer.String(alias);
    //            int type;
    writer.String("type");
    writer.Int(type);
    //            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);
    //
    writer.EndObject();
}
};
