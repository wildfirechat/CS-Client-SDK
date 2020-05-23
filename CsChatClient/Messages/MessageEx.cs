using System;
using System.Collections.Generic;
using CsChatClient.Models;
using Newtonsoft.Json;

namespace CsChatClient.Messages
{
    public class MessageEx : ISerializable
    {
        public long MessageId { get; set; }
        public Conversation Conversation { get; set; }
        public string Sender { get; set; }
        /// <summary>
        /// 消息在会话中定向发送给指定用户
        /// </summary>
        public List<string> ToUsers { get; set; }
        public MessageContent Content { get; set; }
        public MessageDirection Direction { get; set; }
        public MessageStatus Status { get; set; }
        public long MessageUid { get; set; }
        public long ServerTime { get; set; }

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
                        if (reader.Value.Equals("conversation"))
                        {
                            Conversation = (Conversation)JsonTools.GetNextObject(reader, false, typeof(Conversation));
                        }
                        else if (reader.Value.Equals("from"))
                        {
                            Sender = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("messageId"))
                        {
                            MessageId = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("messageUid"))
                        {
                            MessageUid = long.Parse(JsonTools.GetNextString(reader));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            ServerTime = JsonTools.GetNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("content"))
                        {
                            MessagePayload payload = (MessagePayload)JsonTools.GetNextObject(reader, false, typeof(MessagePayload));
                            Content = CsChatClient.ChatClient.Instance().GetContent(payload);
                        }
                        else if (reader.Value.Equals("direction"))
                        {
                            Direction = (MessageDirection)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("to"))
                        {
                            ToUsers = (List<string>)JsonTools.GetNextObject(reader, false, typeof(List<string>));
                        } else if(reader.Value.Equals("status"))
                        {
                            Status = (MessageStatus)JsonTools.GetNextInt(reader);
                        } else
                        {
                            Console.WriteLine("Unknow propterty");
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
