using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = true)]
    public class ContentAttribute : Attribute
    {
        public int type { get; set; }
        public MessageContentPersistFlag flag { get; set; }

        public ContentAttribute(int type, MessageContentPersistFlag flag)
        {
            this.type = type;
            this.flag = flag;
        }

        public ContentAttribute(MessageContentType type, MessageContentPersistFlag flag)
        {
            this.type = (int)type;
            this.flag = flag;
        }
    }
}
