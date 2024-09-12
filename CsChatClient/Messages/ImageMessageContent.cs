namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeImage, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class ImageMessageContent : MediaMessageContent
    {
        /// <summary>
        /// JPEG
        /// </summary>
        public byte[] ThumbnailBytes { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);
            ThumbnailBytes = payload.BinaryContent;
        }

        public override string Digest(MessageEx message)
        {
            return "[图片]";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.SearchableContent = "[图片]";
            payload.BinaryContent = ThumbnailBytes;
            return payload;
        }
    }
}
