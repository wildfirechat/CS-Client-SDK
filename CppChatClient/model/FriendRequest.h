//
//  FriendRequest.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef FriendRequest_hpp
#define FriendRequest_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {
class FriendRequest : public Serializable {
public:
    FriendRequest() : direction(0), status(0), readStatus(0), timestamp(0) {}
    int direction;
    std::string target;
    std::string reason;
    int status;
    int readStatus;
    int64_t timestamp;
    virtual ~FriendRequest(){}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* FriendRequest_hpp */
