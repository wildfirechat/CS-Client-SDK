using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupInfo : Serializable
    {
        public String target;
        public String name;
        public String portrait;
        public String owner;
        public GroupType type;
        public int memberCount;
        public String extra;
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
                        if (reader.Value.Equals("memberCount"))
                        {
                            memberCount = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            updateDt = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("type"))
                        {
                            type = (GroupType)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            target = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            name = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            portrait = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("owner"))
                        {
                            owner = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            extra = JsonTools.getNextString(reader);
                        } else
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
