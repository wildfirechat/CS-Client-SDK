using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChatroomInfo : Serializable
    {
        public String chatRoomId;
        public String title;
        public String desc;
        public String portrait;
        public String extra;
        public int state;
        public int memberCount;
        public long createDt;
        public long updateDt;

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
                        if (reader.Value.Equals("state"))
                        {
                            state = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("memberCount"))
                        {
                            memberCount = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("createDt"))
                        {
                            createDt = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            updateDt = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("chatRoomId"))
                        {
                            chatRoomId = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("title"))
                        {
                            title = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("desc"))
                        {
                            desc = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            portrait = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            extra = JsonTools.getNextString(reader);
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
