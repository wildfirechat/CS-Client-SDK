//
//  UserInfo.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "UserInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {
void UserInfo::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            std::string uid;
    getValue(value, "uid", uid);
//            std::string name;
    getValue(value, "name", name);
//            std::string displayName;
    getValue(value, "displayName", displayName);
//            int gender;
    getValue(value, "gender", gender);
//            std::string portrait;
    getValue(value, "portrait", portrait);
//            std::string mobile;
    getValue(value, "mobile", mobile);
//            std::string email;
    getValue(value, "email", email);
//            std::string address;
    getValue(value, "address", address);
//            std::string company;
    getValue(value, "company", company);
//            std::string social;
    getValue(value, "social", social);
//            std::string extra;
    getValue(value, "extra", extra);
//            //0 normal; 1 robot; 2 thing;
//            int type;
    getValue(value, "type", type);
//            int64_t updateDt;
    getValue(value, "updateDt", updateDt);
    getValue(value, "friendAlias", friendAlias);
    getValue(value, "groupAlias", groupAlias);
    getValue(value, "deleted", deleted);
}

void UserInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            std::string uid;
    writer.String("uid");
    writer.String(uid);
//            std::string name;
    writer.String("name");
    writer.String(name);
//            std::string displayName;
    writer.String("displayName");
    writer.String(displayName);
//            int gender;
    writer.String("gender");
    writer.Int(gender);
//            std::string portrait;
    writer.String("portrait");
    writer.String(portrait);
//            std::string mobile;
    writer.String("mobile");
    writer.String(mobile);
//            std::string email;
    writer.String("email");
    writer.String(email);
//            std::string address;
    writer.String("address");
    writer.String(address);
//            std::string company;
    writer.String("company");
    writer.String(company);
//            std::string social;
    writer.String("social");
    writer.String(social);
//            std::string extra;
    writer.String("extra");
    writer.String(extra);
    
    writer.String("friendAlias");
    writer.String(friendAlias);
    
    writer.String("groupAlias");
    writer.String(groupAlias);
//            //0 normal; 1 robot; 2 thing;
//            int type;
    writer.String("type");
    writer.Int(type);
//            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);
    
    writer.String("deleted");
    writer.Int(deleted);

    writer.EndObject();
}
};
