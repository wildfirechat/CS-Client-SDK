using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TYPING, MessageContentPersistFlag.PersistFlag_TRANSPARENT)]
    class TypingMessageContent : MessageContent
    {
        public static int TYPING_TEXT = 0;
        public static int TYPING_VOICE = 1;
        public static int TYPING_CAMERA = 2;
        public static int TYPING_LOCATION = 3;
        public static int TYPING_FILE = 4;

        private int typingType;

        public override void decode(MessagePayload payload)
        {
            typingType = Int32.Parse(payload.content);
        }

        public override string digest(MessageEx message)
        {
            return "";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.content = typingType + "";
            return payload;
        }
    }
}
