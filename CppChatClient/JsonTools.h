//
//  JsonTools.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef JsonTools_hpp
#define JsonTools_hpp

#include <stdio.h>
#include <string>
#include <list>

#include "rapidjson/rapidjson.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "Serializable.h"
using namespace wfchatjson;

namespace WFCLib {

class Serializable;
extern std::string base64Decode(const std::string &base64str);
extern std::string base64Encode(const std::string &str);

extern bool getValue(const Value &value, const std::string &tag, int &ret);
extern bool getValue(const Value &value, const std::string &tag, long &ret);
extern bool getValue(const Value &value, const std::string &tag, int64_t &ret);
extern bool getValue(const Value &value, const std::string &tag, bool &ret);
extern bool getValue(const Value &value, const std::string &tag, std::string &ret);
extern bool getValue(const Value &value, const std::string &tag, Serializable &ret);
extern bool getValue(const Value &value, const std::string &tag, std::list<std::string> &ret);


class JsonParser {
public:
    JsonParser(const std::string &json);
    ~JsonParser();
    
    bool getValue(const std::string &tag, int &ret);
    bool getValue(const std::string &tag, long &ret);
    bool getValue(const std::string &tag, int64_t &ret);
    bool getValue(const std::string &tag, float &ret);
    bool getValue(const std::string &tag, double &ret);
    bool getValue(const std::string &tag, bool &ret);
    bool getValue(const std::string &tag, std::string &ret);
    bool getValue(const std::string &tag, Serializable &ret);
    bool getValue(const std::string &tag, std::list<std::string> &ret);
    
    bool isParsed() const { return parsed; }
private:
    Document value;
    bool parsed;
};


class JsonBuilder {
public:
    JsonBuilder();
    ~JsonBuilder();
    

    void setValue(const std::string &tag, int value);
    void setValue(const std::string &tag, long value);
    void setValue(const std::string &tag, float value);
    void setValue(const std::string &tag, double value);
    void setValue(const std::string &tag, int64_t value);
    void setValue(const std::string &tag, bool value);
    void setValue(const std::string &tag, const std::string &value);
    void setValue(const std::string &tag, const Serializable *pValue);
    void setValue(const std::string &tag, const std::list<std::string> &value);
    
    std::string build();
private:
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer;
};


extern std::list<std::string> parseStringList(const std::string &json);

};
#endif /* JsonTools_hpp */
