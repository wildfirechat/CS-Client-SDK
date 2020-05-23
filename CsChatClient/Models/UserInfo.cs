using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class UserInfo : ISerializable
    {
        public string Uid { get; set; }
        public string Name { get; set; }
        public string DisplayName { get; set; }

        /// <summary>
        /// 用户在群里面给自己设置的备注，不同群不一样
        /// </summary>
        public string GroupAlias { get; set; }

        /// <summary>
        /// 我为好友设置的备注
        /// </summary>
        public string FriendAlias { get; set; }

        public string Portrait { get; set; }
        public int Gender { get; set; }
        public string Mobile { get; set; }
        public string Email { get; set; }
        public string Address { get; set; }
        public string Company { get; set; }
        public string Social { get; set; }
        public string Extra { get; set; }
        public long UpdateDt { get; set; }

        /// <summary>
        /// 0 normal; 1 robot; 2 thing;
        /// </summary>
        public int Type { get; set; }

        /// <summary>
        /// normal; 1 deleted;
        /// </summary>
        public int Deleted { get; set; }

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
                        if (reader.Value.Equals("gender"))
                        {
                            Gender = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("type"))
                        {
                            Type = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("deleted"))
                        {
                            Deleted = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            UpdateDt = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("uid"))
                        {
                            Uid = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            Name = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("displayName"))
                        {
                            DisplayName = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("groupAlias"))
                        {
                            GroupAlias = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("friendAlias"))
                        {
                            FriendAlias = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            Portrait = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("mobile"))
                        {
                            Mobile = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("email"))
                        {
                            Email = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("address"))
                        {
                            Address = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("company"))
                        {
                            Company = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("social"))
                        {
                            Social = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            Extra = JsonTools.GetNextString(reader);
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