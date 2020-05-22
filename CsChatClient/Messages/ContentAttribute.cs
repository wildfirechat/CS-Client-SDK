using System;

namespace CsChatClient.Messages
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    public class ContentAttribute : Attribute
    {
        public int Type { get; set; }
        public MessageContentPersistFlag Flag { get; set; }

        public ContentAttribute(int type, MessageContentPersistFlag flag)
        {
            this.Type = type;
            this.Flag = flag;
        }

        public ContentAttribute(MessageContentType type, MessageContentPersistFlag flag)
        {
            this.Type = (int)type;
            this.Flag = flag;
        }
    }
}
