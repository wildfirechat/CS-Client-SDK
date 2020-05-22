using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChatroomMemberInfo : ISerializable
    {
        public int MemberCount { get; set; }
        public List<string> Members { get; set; }

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
                        if (reader.Value.Equals("memberCount"))
                        {
                            MemberCount = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("members"))
                        {
                            Members = JsonTools.GetNextStringList(reader, false);
                        }
                        else 
                        {
                            
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
