using System;
using CsChatClient.Messages;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ConversationSearchInfo : ISerializable
    {
        public Conversation Conversation { get; set; }
        /// <summary>
        /// only marchedCount == 1, load the message
        /// </summary>
        public MessageEx MarchedMessage { get; set; }
        public long Timestamp { get; set; }
        public int MarchedCount { get; set; }

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
                        if (reader.Value.Equals("conversation"))
                        {
                            Conversation = (Conversation)JsonTools.GetNextObject(reader, false, typeof(Conversation));
                        }
                        else if (reader.Value.Equals("marchedMessage"))
                        {
                            MarchedMessage = (MessageEx)JsonTools.GetNextObject(reader, false, typeof(MessageEx));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            Timestamp = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("marchedCount"))
                        {
                            MarchedCount = JsonTools.GetNextInt(reader);
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
