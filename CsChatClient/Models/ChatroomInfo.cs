using System;
using Newtonsoft.Json;

namespace CsChatClient.Models
{
    public class ChatroomInfo : ISerializable
    {
        public string ChatRoomId { get; set; }
        public string Title { get; set; }
        public string Desc { get; set; }
        public string Portrait { get; set; }
        public string Extra { get; set; }
        public int State { get; set; }
        public int MemberCount { get; set; }
        public long CreateDt { get; set; }
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
                        if (reader.Value.Equals("state"))
                        {
                            State = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("memberCount"))
                        {
                            MemberCount = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("createDt"))
                        {
                            CreateDt = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("updateDt"))
                        {
                            UpdateDt = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("chatRoomId"))
                        {
                            ChatRoomId = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("title"))
                        {
                            Title = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("desc"))
                        {
                            Desc = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("portrait"))
                        {
                            Portrait = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            Extra = JsonTools.GetNextString(reader);
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
