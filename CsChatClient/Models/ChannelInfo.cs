using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChannelInfo : Serializable
    {
        public String channelId;
        public String name;
        public String portrait;
        public String desc;
        public String owner;
        public int status;
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
                        if (reader.Value.Equals("status"))
                        {
                            status = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("channelId"))
                        {
                            channelId = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            name = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            portrait = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("desc"))
                        {
                            desc = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("owner"))
                        {
                            owner = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            extra = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            updateDt = JsonTools.getNextBigInt(reader);
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
