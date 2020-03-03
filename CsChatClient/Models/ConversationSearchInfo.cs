using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CsChatClient.Messages;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ConversationSearchInfo : Serializable
    {
        public Conversation conversation;
        //only marchedCount == 1, load the message
        public MessageEx marchedMessage;
        public long timestamp;
        public int marchedCount;

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
                            conversation = (Conversation)JsonTools.getNextObject(reader, false, typeof(Conversation));
                        }
                        else if (reader.Value.Equals("marchedMessage"))
                        {
                            marchedMessage = (MessageEx)JsonTools.getNextObject(reader, false, typeof(MessageEx));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            timestamp = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("marchedCount"))
                        {
                            marchedCount = JsonTools.getNextInt(reader);
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
