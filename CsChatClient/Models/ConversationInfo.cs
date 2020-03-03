using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CsChatClient.Messages;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ConversationInfo : Serializable
    {
        public Conversation conversation;
        public MessageEx lastMessage;
        public long timestamp;
        public String draft;
        public UnreadCount unreadCount;
        public bool isTop;
        public bool isSilent;

        public void Serialize(JsonWriter writer)
        {
            throw new NotImplementedException();
        }

        public bool Unserialize(JsonReader reader)
        {
            conversation = new Conversation();
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.PropertyName:
                        if (reader.Value.Equals("conversationType"))
                        {
                            conversation.type = (ConversationType)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            conversation.target = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("line"))
                        {
                            conversation.line = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("lastMessage"))
                        {
                            lastMessage = (MessageEx)JsonTools.getNextObject(reader, false, typeof(MessageEx));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            timestamp = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("draft"))
                        {
                            draft = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("unreadCount"))
                        {
                            unreadCount = (UnreadCount)JsonTools.getNextObject(reader, false, typeof(UnreadCount));
                        }
                        else if (reader.Value.Equals("isTop"))
                        {
                            isTop = JsonTools.getNextBoolean(reader);
                        }
                        else if (reader.Value.Equals("isSilent"))
                        {
                            isSilent = JsonTools.getNextBoolean(reader);
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
