using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;


namespace CsChatClient.Models
{
    public class UnreadCount : Serializable
    {
        /**
 * 单聊未读数
 */
        public int unread;
        /**
         * 群聊@数
         */
        public int unreadMention;
        /**
         * 群聊@All数
         */
        public int unreadMentionAll;

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
                            unread = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("unreadMention"))
                        {
                            unreadMention = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("unreadMentionAll"))
                        {
                            unreadMentionAll = JsonTools.getNextInt(reader);
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
