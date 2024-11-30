//
//  Serializable.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/29.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef Serializable_hpp
#define Serializable_hpp

#include <stdio.h>
#include <string>
#include <list>

namespace WFCLib {

class Serializable {
public:
    Serializable() {}
    virtual ~Serializable() {}
    
    virtual void Serialize(void *writer) const = 0;
    virtual void Unserialize(const void *value) = 0;
    
    
    bool fromJson(std::string jsonStr);
    std::string toJson() const;
    static std::string list2Json(std::list<std::string> &strs);
    static std::string list2Json(std::list<int> &is);
    static std::string longlongToStr(long long llv);
};
};
#endif /* Serializable_hpp */
