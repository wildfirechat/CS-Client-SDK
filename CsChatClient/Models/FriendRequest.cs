using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class FriendRequest : Serializable
    {
        public int direction;
        public String target;
        public String reason;
        //    RequestStatus_Sent = 0,
        //    RequestStatus_Accepted = 1,
        //    RequestStatus_Rejected = 3
        public int status;
        public int readStatus;
        public long timestamp;

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
                        if (reader.Value.Equals("direction"))
                        {
                            direction = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("status"))
                        {
                            status = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("readStatus"))
                        {
                            readStatus = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            timestamp = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            target = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("reason"))
                        {
                            reason = JsonTools.getNextString(reader);
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
