using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class GroupSearchInfo : ISerializable
    {
        public GroupInfo GroupInfo { get; set; }
        /// <summary>
        /// 0 march group name, 1 march group member name, 2 both
        /// </summary>
        public int MarchedType { get; set; }
        public List<string> MarchedMembers { get; set; }

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
                            GroupInfo = (GroupInfo)JsonTools.GetNextObject(reader, false, typeof(GroupInfo));
                        }
                        else if (reader.Value.Equals("marchedType"))
                        {
                            MarchedType = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("marchedMembers"))
                        {
                            MarchedMembers = JsonTools.GetNextStringList(reader, false);
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
