using System;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeTyping, MessageContentPersistFlag.PersistFlagTransparent)]
    public class TypingMessageContent : MessageContent
    {
        public const int TypingText = 0;
        public const int TypingVoice = 1;
        public const int TypingCamera = 2;
        public const int TypingLocation = 3;
        public const int TypingFile = 4;

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
