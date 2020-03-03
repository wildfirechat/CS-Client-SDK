//
//  UserSettingEntry.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "UserSettingEntry.h"
#include "../JsonTools.h"
    
namespace WFCLib {

void UserSettingEntry::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            UserSettingScope scope;
    int iscope = -1;
    getValue(value, "scope", iscope);
    if (iscope != -1) {
        scope = (UserSettingScope)iscope;
    }

//            std::string key;
    getValue(value, "key", key);
//            std::string value;
    getValue(value, "value", this->value);
//            int64_t updateDt;
    getValue(value, "updateDt", updateDt);
}

void UserSettingEntry::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            UserSettingScope scope;
    writer.String("scope");
    writer.Int((int)scope);
//            std::string key;
    writer.String("key");
    writer.String(key);
//            std::string value;
    writer.String("value");
    writer.String(value);
//            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);
//
    writer.EndObject();
}
};
