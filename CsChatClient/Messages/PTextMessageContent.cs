namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_P_TEXT, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class PTextMessageContent : MessageContent
    {
        public string Content { get; set; }

        public override void Decode(MessagePayload payload)
        {
            Content = payload.Content;
        }

        public override string Digest(MessageEx message)
        {
            return Content;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.Content = Content;
            return payload;
        }
    }
}
