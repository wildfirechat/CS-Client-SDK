//
//  FriendRequest.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "FriendRequest.h"
#include "../JsonTools.h"
    
namespace WFCLib {

void FriendRequest::Unserialize(const void *pvalue) {
    const Value& value = *((const Value *)pvalue);
    if (!value.IsObject()) {
        return;
    }

//            int direction;
    getValue(value, "direction", direction);
//            std::string target;
    getValue(value, "target", target);
//            std::string reason;
    getValue(value, "reason", reason);
//            int status;
    getValue(value, "status", status);
//            int readStatus;
    getValue(value, "readStatus", readStatus);
//            int64_t timestamp;
    getValue(value, "timestamp", timestamp);
}

void FriendRequest::Serialize(void *pwriter) const {
    Writer<StringBuffer> &writer = *((Writer<StringBuffer> *)pwriter);

    writer.StartObject();

//            int direction;
    writer.String("direction");
    writer.Int(direction);
//            std::string target;
    writer.String("target");
    writer.String(target);
//            std::string reason;
    writer.String("reason");
    writer.String(reason);
//            int status;
    writer.String("status");
    writer.Int(status);
//            int readStatus;
    writer.String("readStatus");
    writer.Int(readStatus);
//            int64_t timestamp;
    writer.String("timestamp");
    writer.Int64(timestamp);

    writer.EndObject();
}
};
