using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    public abstract class MessageContent
    {
        public abstract MessagePayload encode();

        public abstract void decode(MessagePayload payload);

        public abstract String digest(MessageEx message);

        //0 普通消息, 1 部分提醒, 2 提醒全部
        public int mentionedType;

        //提醒对象，mentionedType 1时有效
        public List<String> mentionedTargets;
        public String extra;

        public int getType()
        {
            Type type = GetType();

            ContentAttribute attribute = (ContentAttribute)Attribute.GetCustomAttribute(type, typeof(ContentAttribute));
            if (attribute != null)
            {
                return attribute.type;
            }
            
            return 0;
        }

        public MessageContentPersistFlag getFlag()
        {
            Type type = GetType();
            PropertyInfo[] propInfos = type.GetProperties();
            foreach (var prop in propInfos)
            {
                string parameterName = prop.Name;
                if (prop.IsDefined(typeof(ContentAttribute), false))
                {
                    ContentAttribute attribute = (ContentAttribute)prop.GetCustomAttribute(typeof(ContentAttribute), false);
                    return attribute.flag;
                }
            }
            return MessageContentPersistFlag.PersistFlag_NOT_PERSIST;
        }
    }
}
