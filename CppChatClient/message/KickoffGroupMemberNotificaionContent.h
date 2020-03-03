//
//  KickoffGroupMemberNotificaionContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef KickoffGroupMemberNotificaionContent_hpp
#define KickoffGroupMemberNotificaionContent_hpp
#include "NotificationMessageContent.h"

namespace WFCLib {
class KickoffGroupMemberNotificaionContentPrototype;
class KickoffGroupMemberNotificaionContent : public NotificationMessageContent
{
public:
    KickoffGroupMemberNotificaionContent() {}
    virtual ~KickoffGroupMemberNotificaionContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const;
    virtual std::string formatNotification(const Message &msg) const;
    virtual const MessageContentPrototype* getPrototype() const;
public:
    std::string groupId;
    std::string operatorId;
    std::list<std::string> kickedMembers;
    static KickoffGroupMemberNotificaionContentPrototype sPrototype;
};

class KickoffGroupMemberNotificaionContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST; }
    virtual MessageContentType getType() const { return MESSAGE_CONTENT_TYPE_KICKOF_GROUP_MEMBER; }
    virtual MessageContent *productEmptyContent() const { return new KickoffGroupMemberNotificaionContent(); }
};
};
#endif /* KickoffGroupMemberNotificaionContent_hpp */
