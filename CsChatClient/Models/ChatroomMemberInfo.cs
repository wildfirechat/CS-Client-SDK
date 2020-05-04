using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChatroomMemberInfo : Serializable
    {
        public int memberCount;
        public List<String> members;

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
                            memberCount = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("members"))
                        {
                            members = JsonTools.getNextStringList(reader, false);
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
