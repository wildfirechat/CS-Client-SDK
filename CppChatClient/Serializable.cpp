//
//  Serializable.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "Serializable.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"


using namespace wfchatjson;

namespace WFCLib {
bool Serializable::fromJson(std::string jsonStr) {
    Document document;
    if (document.Parse(jsonStr).HasParseError()) {
        printf("\nParsing to document failure(%s).\n", jsonStr.c_str());
        return false;
    }
    
    Unserialize(&document);
    return true;
}
std::string Serializable::toJson() const {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    Serialize(&writer);
    return sb.GetString();
}

std::string Serializable::list2Json(std::list<std::string> &strs) {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    writer.StartArray();
    for (std::list<std::string>::const_iterator it = strs.begin(); it != strs.end(); it++) {
        const std::string &o = *it;
        writer.String(o);
    }
    writer.EndArray();

    return sb.GetString();
}

std::string Serializable::list2Json(std::list<int> &is) {
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    writer.StartArray();
    for (std::list<int>::const_iterator it = is.begin(); it != is.end(); it++) {
        const int &o = *it;
        writer.Int(o);
    }
    writer.EndArray();

    return sb.GetString();
}

};
