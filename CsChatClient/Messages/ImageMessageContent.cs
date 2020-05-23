namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_IMAGE, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class ImageMessageContent : MediaMessageContent
    {
        /// <summary>
        /// JPEG
        /// </summary>
        public byte[] ThumbnailBytes { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);
            payload.BinaryContent = ThumbnailBytes;
        }

        public override string Digest(MessageEx message)
        {
            return "[图片]";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.BinaryContent = ThumbnailBytes;
            return payload;
        }
    }
}
