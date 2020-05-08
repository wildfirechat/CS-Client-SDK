using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_IMAGE, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class ImageMessageContent : MediaMessageContent
    {
        //jpeg
        public byte[] thumbnailBytes;

        public override void decode(MessagePayload payload)
        {
            base.decode(payload);
            payload.binaryContent = thumbnailBytes;
        }

        public override string digest(MessageEx message)
        {
            return "[图片]";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = base.encode();
            payload.binaryContent = thumbnailBytes;
            return payload;
        }
    }
}
