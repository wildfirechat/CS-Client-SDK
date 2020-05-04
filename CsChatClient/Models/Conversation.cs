using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class Conversation : Serializable
    {
        public Conversation() { }
        public Conversation(ConversationType type, string target, int line)
        {
            this.type = type;
            this.target = target;
            this.line = line;
        }
        public ConversationType type;
        public string target;
        // 可以用来做自定义会话，区分不同业务线
        public int line;

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
                        if (reader.Value.Equals("conversationType"))
                        {
                            type = (ConversationType)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            target = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("line"))
                        {
                            line = JsonTools.getNextInt(reader);
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
