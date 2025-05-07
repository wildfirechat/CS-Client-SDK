using System;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeFile, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class FileMessageContent : MediaMessageContent
    {
        public string Name { get; set; }
        public long Size { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);
            Name = payload.SearchableContent;
            if(Name.Contains("[文件]"))
            {
                Name = Name.Replace("[文件]", "");
            }
            Size = long.Parse(payload.Content);
        }

        public override string Digest(MessageEx message)
        {
            return "[文件]" + Name;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.SearchableContent = "[文件]" + Name;
            payload.Content = Size + "";
            payload.MediaType = MediaType.MediaTypeFile;
            return payload;
        }
    }
}
