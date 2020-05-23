using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class Conversation : ISerializable
    {
        public Conversation() { }
        public Conversation(ConversationType type, string target, int line)
        {
            this.Type = type;
            this.Target = target;
            this.Line = line;
        }
        public ConversationType Type { get; set; }
        public string Target { get; set; }
        /// <summary>
        /// 可以用来做自定义会话，区分不同业务线
        /// </summary>
        public int Line { get; set; }

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
                            Type = (ConversationType)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            Target = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("line"))
                        {
                            Line = JsonTools.GetNextInt(reader);
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
