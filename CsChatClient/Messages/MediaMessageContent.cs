namespace CsChatClient.Messages
{
    public abstract class MediaMessageContent : MessageContent
    {
        public string LocalPath { get; set; }
        public string RemoteUrl { get; set; }
        public MediaType MediaType { get; set; }

        override
        public MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.LocalMediaPath = LocalPath;
            payload.RemoteMediaUrl = RemoteUrl;
            payload.MediaType = MediaType;
            return payload;
        }

        override
        public void Decode(MessagePayload payload)
        {
            LocalPath = payload.LocalMediaPath;
            RemoteUrl = payload.RemoteMediaUrl;
            MediaType = payload.MediaType;
        }
    }
}
