using System;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_FILE, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class FileMessageContent : MediaMessageContent
    {
        public string Name { get; set; }
        public int Size { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);
            Name = payload.SearchableContent;
            if(Name.Contains("[文件]"))
            {
                Name = Name.Replace("[文件]", "");
            }
            Size = int.Parse(payload.Content);
        }

        public override string Digest(MessageEx message)
        {
            return "[文件]" + Name;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.SearchableContent = Name;
            payload.Content = Size + "";
            payload.MediaType = MediaType.Media_Type_File;
            return payload;
        }
    }
}
