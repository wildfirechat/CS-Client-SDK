using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_FILE, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class FileMessageContent : MediaMessageContent
    {
        public string name;
        public int size;

        public override void decode(MessagePayload payload)
        {
            base.decode(payload);
            name = payload.searchableContent;
            if(name.Contains("[文件]"))
            {
                name = name.Replace("[文件]", "");
            }
            size = Int32.Parse(payload.content);
        }

        public override string digest(MessageEx message)
        {
            return "[文件]" + name;
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = base.encode();
            payload.searchableContent = name;
            payload.content = size + "";
            return payload;
        }
    }
}
