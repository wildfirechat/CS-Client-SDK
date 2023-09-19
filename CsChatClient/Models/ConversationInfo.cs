using System;
using CsChatClient.Messages;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ConversationInfo : ISerializable
    {
        public Conversation Conversation { get; set; }
        public MessageEx LastMessage { get; set; }
        public long Timestamp { get; set; }
        public string Draft { get; set; }
        public UnreadCount UnreadCount { get; set; }
        public int IsTop { get; set; }
        public bool IsSilent { get; set; }

        public void Serialize(JsonWriter writer)
        {
            throw new NotImplementedException();
        }

        public bool Unserialize(JsonReader reader)
        {
            Conversation = new Conversation();
            while (reader.Read())
            {
                switch (reader.TokenType)
                {
                    case JsonToken.PropertyName:
                        if (reader.Value.Equals("conversationType"))
                        {
                            Conversation.Type = (ConversationType)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            Conversation.Target = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("line"))
                        {
                            Conversation.Line = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("lastMessage"))
                        {
                            LastMessage = (MessageEx)JsonTools.GetNextObject(reader, false, typeof(MessageEx));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            Timestamp = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("draft"))
                        {
                            Draft = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("unreadCount"))
                        {
                            UnreadCount = (UnreadCount)JsonTools.GetNextObject(reader, false, typeof(UnreadCount));
                        }
                        else if (reader.Value.Equals("isTop"))
                        {
                            IsTop = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("isSilent"))
                        {
                            IsSilent = JsonTools.GetNextBoolean(reader);
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
