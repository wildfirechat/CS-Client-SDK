using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ReadEntry : ISerializable
    {
        public Conversation Conversation { get; set; }
        public string UserId { get; set; }
        public long ReadDT { get; set; }

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
                        if (reader.Value.Equals("userId"))
                        {
                            UserId = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("conversationType"))
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
                        else if (reader.Value.Equals("readDt"))
                        {
                            ReadDT = JsonTools.GetNextBigInt(reader);
                        }
                        else
                        {
                            Console.WriteLine("Unexpacted json property");
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
