using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChannelInfo : ISerializable
    {
        public string ChannelId { get; set; }
        public string Name { get; set; }
        public string Portrait { get; set; }
        public string Desc { get; set; }
        public string Owner { get; set; }
        public int Status { get; set; }
        public string Extra { get; set; }
        public long UpdateDt { get; set; }

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
                            Status = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("channelId"))
                        {
                            ChannelId = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            Name = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            Portrait = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("desc"))
                        {
                            Desc = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("owner"))
                        {
                            Owner = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            Extra = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            UpdateDt = JsonTools.GetNextBigInt(reader);
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
