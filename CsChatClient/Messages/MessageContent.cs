using System;
using System.Collections.Generic;
using System.Reflection;

namespace CsChatClient.Messages
{
    public abstract class MessageContent
    {
        public abstract MessagePayload Encode();

        public abstract void Decode(MessagePayload payload);

        public abstract string Digest(MessageEx message);

        /// <summary>
        /// 0 普通消息, 1 部分提醒, 2 提醒全部
        /// </summary>
        public int MentionedType { get; set; }

        /// <summary>
        /// 提醒对象，mentionedType 1时有效
        /// </summary>
        public List<string> MentionedTargets { get; set; }

        public string Extra { get; set; }

        public int GetMessageType()
        {
            Type type = GetType();

            ContentAttribute attribute = (ContentAttribute)Attribute.GetCustomAttribute(type, typeof(ContentAttribute));
            if (attribute != null)
            {
                return attribute.Type;
            }
            
            return 0;
        }

        public MessageContentPersistFlag GetFlag()
        {
            Type type = GetType();
            PropertyInfo[] propInfos = type.GetProperties();
            foreach (var prop in propInfos)
            {
                string parameterName = prop.Name;
                if (prop.IsDefined(typeof(ContentAttribute), false))
                {
                    ContentAttribute attribute = (ContentAttribute)prop.GetCustomAttribute(typeof(ContentAttribute), false);
                    return attribute.Flag;
                }
            }
            return MessageContentPersistFlag.PersistFlag_NOT_PERSIST;
        }
    }
}
