//
//  ChannelInfo.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "ChannelInfo.h"
#include "../JsonTools.h"
    
namespace WFCLib {

void ChannelInfo::Unserialize(const void *pvalue) {
const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            std::string channelId;
    getValue(value, "channelId", channelId);
//            std::string name;
    getValue(value, "name", name);
//            std::string portrait;
    getValue(value, "portrait", portrait);
//            std::string owner;
    getValue(value, "owner", owner);
//            int status;
    getValue(value, "status", status);
//            std::string desc;
    getValue(value, "desc", desc);
//            std::string extra;
    getValue(value, "extra", extra);
//            std::string secret;
    getValue(value, "secret", secret);
//            std::string callback;
    getValue(value, "callback", callback);
//            int64_t updateDt;
    getValue(value, "updateDt", updateDt);
//            int automatic;
    getValue(value, "automatic", automatic);
}

void ChannelInfo::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            std::string channelId;
    writer.String("channelId");
    writer.String(channelId);
//            std::string name;
    writer.String("name");
    writer.String(name);
//            std::string portrait;
    writer.String("portrait");
    writer.String(portrait);
//            std::string owner;
    writer.String("owner");
    writer.String(owner);
//            int status;
    writer.String("status");
    writer.Int(status);
//            std::string desc;
    writer.String("desc");
    writer.String(desc);
//            std::string extra;
    writer.String("extra");
    writer.String(extra);
//            std::string secret;
    writer.String("secret");
    writer.String(secret);
//            std::string callback;
    writer.String("callback");
    writer.String(callback);
//            int64_t updateDt;
    writer.String("updateDt");
    writer.Int64(updateDt);
//            int automatic;
    writer.String("automatic");
    writer.Int(automatic);

    writer.EndObject();
}
};
