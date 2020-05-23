using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class FriendRequest : ISerializable
    {
        public int Direction { get; set; }
        public string Target { get; set; }
        public string Reason { get; set; }
        /// <summary>
        /// RequestStatus_Sent = 0,
        /// RequestStatus_Accepted = 1,
        /// RequestStatus_Rejected = 3
        /// </summary>
        public int Status { get; set; }
        public int ReadStatus { get; set; }
        public long Timestamp { get; set; }

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
                            Direction = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("status"))
                        {
                            Status = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("readStatus"))
                        {
                            ReadStatus = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            Timestamp = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("target"))
                        {
                            Target = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("reason"))
                        {
                            Reason = JsonTools.GetNextString(reader);
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
