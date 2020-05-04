using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupSearchInfo : Serializable
    {
        public GroupInfo groupInfo;
        //0 march group name, 1 march group member name, 2 both
        public int marchedType;
        public List<String> marchedMembers;

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
                        if (reader.Value.Equals("groupInfo"))
                        {
                            groupInfo = (GroupInfo)JsonTools.getNextObject(reader, false, typeof(GroupInfo));
                        }
                        else if (reader.Value.Equals("marchedType"))
                        {
                            marchedType = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("marchedMembers"))
                        {
                            marchedMembers = JsonTools.getNextStringList(reader, false);
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
