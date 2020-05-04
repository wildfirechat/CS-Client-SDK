using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class UserInfo : Serializable
    {
        public String uid;
        public String name;
        public String displayName;
        // 用户在群里面给自己设置的备注，不同群不一样
        public String groupAlias;
        // 我为好友设置的备注
        public String friendAlias;
        public String portrait;
        public int gender;
        public String mobile;
        public String email;
        public String address;
        public String company;
        public String social;
        public String extra;
        public long updateDt;
        //0 normal; 1 robot; 2 thing;
        public int type;
        //0 normal; 1 deleted;
        public int deleted;

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
                            gender = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("type"))
                        {
                            type = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("deleted"))
                        {
                            deleted = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            updateDt = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("uid"))
                        {
                            uid = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("name"))
                        {
                            name = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("displayName"))
                        {
                            displayName = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("groupAlias"))
                        {
                            groupAlias = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("friendAlias"))
                        {
                            friendAlias = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            portrait = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("mobile"))
                        {
                            mobile = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("email"))
                        {
                            email = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("address"))
                        {
                            address = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("company"))
                        {
                            company = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("social"))
                        {
                            social = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            extra = JsonTools.getNextString(reader);
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
