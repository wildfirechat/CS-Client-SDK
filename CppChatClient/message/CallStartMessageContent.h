//
//  CallStartMessageContent.hpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef CallStartMessageContent_hpp
#define CallStartMessageContent_hpp

#include "MessageContent.h"

namespace WFCLib {

class CallStartMessageContentPrototype;
class CallStartMessageContent : public MessageContent
{
public:
    CallStartMessageContent() : connectTime(0), endTime(0), status(0), audioOnly(false) {}
    virtual ~CallStartMessageContent() {}
    
    virtual MessagePayload encode() const;
    virtual void decode(const MessagePayload &payload);
    
    virtual MessageContent* clone() const;
    virtual std::string digest() const { return audioOnly ? "[音频通话]" : "[视频通话]"; }
    virtual const MessageContentPrototype* getPrototype() const;
    
public:
    std::string callId;
    std::list<std::string> targetIds;
    int64_t connectTime;
    int64_t endTime;
    /* 结束原因
    WFAVCallEndReason
     0: kWFAVCallEndReasonUnknown,
     1: kWFAVCallEndReasonBusy,
     2: kWFAVCallEndReasonSignalError,
     3: kWFAVCallEndReasonHangup,
     4: kWFAVCallEndReasonMediaError,
     5: kWFAVCallEndReasonRemoteHangup,
     6: kWFAVCallEndReasonOpenCameraFailure,
     7: kWFAVCallEndReasonTimeout,
     8: kWFAVCallEndReasonAcceptByOtherClient
     */
    int status;
    bool audioOnly;
    
    static CallStartMessageContentPrototype sPrototype;
};

class CallStartMessageContentPrototype : public MessageContentPrototype {
    virtual MessageContentPersistFlag getFlag() const { return PersistFlag_PERSIST_AND_COUNT; }
    virtual MessageContentType getType() const { return VOIP_CONTENT_TYPE_START; }
    virtual MessageContent *productEmptyContent() const { return new CallStartMessageContent(); }
};
};
#endif /* CallStartMessageContent_hpp */
