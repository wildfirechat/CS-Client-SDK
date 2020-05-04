using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupMember : Serializable
    {
        public String groupId;
        public String memberId;
        public String alias;
        public GroupMemberType type;
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
                        if (reader.Value.Equals("type"))
                        {
                            type = (GroupMemberType)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            updateDt = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("groupId"))
                        {
                            groupId = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("memberId"))
                        {
                            memberId = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("alias"))
                        {
                            alias = JsonTools.getNextString(reader);
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
