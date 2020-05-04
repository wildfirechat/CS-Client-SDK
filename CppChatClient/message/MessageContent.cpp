#include "MessageContent.h"

namespace WFCLib {
MessagePayload MessageContent::encode() const {
    MessagePayload payload;
    payload.contentType = getPrototype()->getType();
    payload.extra = extra;
    return payload;
}

void MessageContent::decode(const MessagePayload &payload) {
    extra = payload.extra;
}
};
