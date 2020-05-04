//
//  UnreadCount.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef UnreadCount_hpp
#define UnreadCount_hpp

#include <stdio.h>
#include "../Serializable.h"

namespace WFCLib {

class UnreadCount : public Serializable {
public:
    UnreadCount() : unread(0), unreadMention(0), unreadMentionAll(0) {}
    virtual ~UnreadCount() {}
    int unread;
    int unreadMention;
    int unreadMentionAll;

    virtual void Serialize(void *writer) const;
    virtual void Unserialize(const void *value);
};
};
#endif /* UnreadCount_hpp */
