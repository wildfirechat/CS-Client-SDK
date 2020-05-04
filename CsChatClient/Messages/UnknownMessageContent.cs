using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_UNKNOWN, MessageContentPersistFlag.PersistFlag_NOT_PERSIST)]
    public class UnknownMessageContent : MessageContent
    {
        public MessagePayload rawPayload;
  
        public override void decode(MessagePayload payload)
        {
            rawPayload = payload;
        }

        public override string digest(MessageEx message)
        {
            return "Unknown message content";
        }

        public override MessagePayload encode()
        {
            return rawPayload;
        }
    }
}
