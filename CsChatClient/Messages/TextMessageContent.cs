using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TEXT, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class TextMessageContent : MessageContent
    {
        public string content;

        public override void decode(MessagePayload payload)
        {
            content = payload.searchableContent;    
        }

        public override string digest(MessageEx message)
        {
            return content;
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.searchableContent = content;
            return payload;
        }
    }
}
