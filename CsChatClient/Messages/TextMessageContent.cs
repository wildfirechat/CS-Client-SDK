namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeText, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class TextMessageContent : MessageContent
    {
        public string Content { get; set; }

        public override void Decode(MessagePayload payload)
        {
            Content = payload.SearchableContent;    
        }

        public override string Digest(MessageEx message)
        {
            return Content;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.SearchableContent = Content;
            return payload;
        }
    }
}
