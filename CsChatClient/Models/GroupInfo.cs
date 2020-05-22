using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupInfo : ISerializable
    {
        public string Target { get; set; }
        public string Name { get; set; }
        public string Portrait { get; set; }
        public string Owner { get; set; }
        public GroupType Type { get; set; }
        public int MemberCount { get; set; }
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
                        if (reader.Value.Equals("memberCount"))
                        {
                            MemberCount = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            UpdateDt = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("type"))
                        {
                            Type = (GroupType)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            Target = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            Name = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            Portrait = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("owner"))
                        {
                            Owner = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            Extra = JsonTools.GetNextString(reader);
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
