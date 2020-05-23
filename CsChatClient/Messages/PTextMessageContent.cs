namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypePText, MessageContentPersistFlag.PersistFlagPersistAndCount)]
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
