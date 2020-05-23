using System;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TYPING, MessageContentPersistFlag.PersistFlag_TRANSPARENT)]
    public class TypingMessageContent : MessageContent
    {
        public static int TYPING_TEXT = 0;
        public static int TYPING_VOICE = 1;
        public static int TYPING_CAMERA = 2;
        public static int TYPING_LOCATION = 3;
        public static int TYPING_FILE = 4;

        private int _typingType;

        public override void Decode(MessagePayload payload)
        {
            _typingType = int.Parse(payload.Content);
        }

        public override string Digest(MessageEx message)
        {
            return "";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.Content = _typingType + "";
            return payload;
        }
    }
}
