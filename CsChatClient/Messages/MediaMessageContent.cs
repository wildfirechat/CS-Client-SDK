using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    public abstract class MediaMessageContent : MessageContent
    {
        public string localPath;
        public string remoteUrl;
        public MediaType mediaType;

        override
        public MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.localContent = localPath;
            payload.remoteMediaUrl = remoteUrl;
            payload.mediaType = mediaType;
            return payload;
        }

        override
        public void decode(MessagePayload payload)
        {
            localPath = payload.localContent;
            remoteUrl = payload.remoteMediaUrl;
            mediaType = payload.mediaType;
        }
    }
}
