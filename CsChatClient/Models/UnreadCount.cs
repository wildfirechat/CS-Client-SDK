using System;
using Newtonsoft.Json;


namespace CsChatClient.Models
{
    public class UnreadCount : ISerializable
    {
        /// <summary>
        /// 单聊未读数
        /// </summary>
        public int Unread { get; set; }
        /// <summary>
        /// 群聊@数
        /// </summary>
        public int UnreadMention { get; set; }
        /// <summary>
        /// 群聊@All数
        /// </summary>
        public int UnreadMentionAll { get; set; }

        public void Serialize(JsonWriter writer)
        {
            throw new NotImplementedException();
        }

        public bool Unserialize(JsonReader reader)
        {
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.PropertyName:
                        if (reader.Value.Equals("unread"))
                        {
                            Unread = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("unreadMention"))
                        {
                            UnreadMention = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("unreadMentionAll"))
                        {
                            UnreadMentionAll = JsonTools.GetNextInt(reader);
                        }
                        break;
                    case JsonToken.EndObject:
                        return true;
                }
            }
            return false;
        }
    }
}
