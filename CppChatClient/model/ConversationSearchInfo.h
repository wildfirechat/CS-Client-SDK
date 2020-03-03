//
//  ConversationSearchresult.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef ConversationSearchresult_hpp
#define ConversationSearchresult_hpp

#include <stdio.h>
#include "../Serializable.h"
#include "../message/Message.h"

namespace WFCLib {
class ConversationSearchInfo : public Serializable {
public:
    ConversationSearchInfo() : conversationType(0), line(0), marchedMessage(), timestamp(0), marchedCount(0)  {}
    int conversationType;
    std::string target;
    int line;
    //only marchedCount == 1, load the message
    Message marchedMessage;
    int64_t timestamp;
    int marchedCount;
    virtual ~ConversationSearchInfo(){}
    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *pvalue);
};
};
#endif /* ConversationSearchresult_hpp */
