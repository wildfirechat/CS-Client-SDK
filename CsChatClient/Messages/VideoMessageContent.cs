namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.VoipContentTypeStart, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class VideoMessageContent : MediaMessageContent
    {
        public byte[] ThumbnailData { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);
            ThumbnailData = payload.BinaryContent;
        }

        public override string Digest(MessageEx message)
        {
            return "[视频]";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.BinaryContent = ThumbnailData;
            return payload;
        }
    }
}
