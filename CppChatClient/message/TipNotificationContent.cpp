//
//  TipNotificationContent.cpp
//  ChatClient
//
//  Created by Hao Jia on 2020/1/31.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#include "TipNotificationContent.h"

namespace WFCLib {

TipNotificationContentPrototype TipNotificationContent::sPrototype;

MessagePayload TipNotificationContent::encode() const {
    MessagePayload payload;
    payload.extra = extra;
    payload.content = tip;
    return payload;
}

void TipNotificationContent::decode(const MessagePayload & payload) {
    extra = payload.extra;
    tip = payload.content;
}


MessageContent* TipNotificationContent::clone() const {
    TipNotificationContent *p = new TipNotificationContent();
    p->extra = extra;
    p->tip = tip;
    return p;
}

const MessageContentPrototype* TipNotificationContent::getPrototype() const {
    return &sPrototype;
}

std::string TipNotificationContent::digest() const {
    return tip;
}

std::string TipNotificationContent::formatNotification(const Message &msg) const {
    return tip;
}
};
