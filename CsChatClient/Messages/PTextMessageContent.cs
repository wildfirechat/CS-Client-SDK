using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_P_TEXT, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class PTextMessageContent : MessageContent
    {
        public string content;

        public override void decode(MessagePayload payload)
        {
            content = payload.content;
        }

        public override string digest(MessageEx message)
        {
            return content;
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.content = content;
            return payload;
        }
    }
}
