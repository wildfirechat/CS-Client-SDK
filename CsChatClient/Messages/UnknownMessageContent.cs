namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_UNKNOWN, MessageContentPersistFlag.PersistFlag_NOT_PERSIST)]
    public class UnknownMessageContent : MessageContent
    {
        public MessagePayload RawPayload { get; set; }

        public override void Decode(MessagePayload payload)
        {
            RawPayload = payload;
        }

        public override string Digest(MessageEx message)
        {
            return "Unknown message content";
        }

        public override MessagePayload Encode()
        {
            return RawPayload;
        }
    }
}
