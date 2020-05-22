using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupMember : ISerializable
    {
        public string GroupId { get; set; }
        public string MemberId { get; set; }
        public string Alias { get; set; }
        public GroupMemberType Type { get; set; }
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
                        if (reader.Value.Equals("type"))
                        {
                            Type = (GroupMemberType)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            UpdateDt = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("groupId"))
                        {
                            GroupId = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("memberId"))
                        {
                            MemberId = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("alias"))
                        {
                            Alias = JsonTools.GetNextString(reader);
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
