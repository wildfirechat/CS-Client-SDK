using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.VOIP_CONTENT_TYPE_START, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class VideoMessageContent : MediaMessageContent
    {
        public byte[] thumbnailData;

        public override void decode(MessagePayload payload)
        {
            base.decode(payload);
            thumbnailData = payload.binaryContent;
        }

        public override string digest(MessageEx message)
        {
            return "[视频]";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = base.encode();
            payload.binaryContent = thumbnailData;
            return payload;
        }
    }
}
