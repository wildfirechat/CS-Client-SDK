using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CsChatClient.Models;
using Newtonsoft.Json;

namespace CsChatClient.Messages
{
    public class MessageEx : Serializable
    {
        public long messageId;
        public Conversation conversation;
        public String sender;
        /**
         * 消息在会话中定向发送给指定用户
         */
        public List<String> toUsers;
        public MessageContent content;
        public MessageDirection direction;
        public MessageStatus status;
        public long messageUid;
        public long serverTime;

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
                            conversation = (Conversation)JsonTools.getNextObject(reader, false, typeof(Conversation));
                        }
                        else if (reader.Value.Equals("from"))
                        {
                            sender = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("messageId"))
                        {
                            messageId = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("messageUid"))
                        {
                            messageUid = long.Parse(JsonTools.getNextString(reader));
                        }
                        else if (reader.Value.Equals("timestamp"))
                        {
                            serverTime = JsonTools.getNextBigInt(reader);
                        }
                        else if (reader.Value.Equals("content"))
                        {
                            MessagePayload payload = (MessagePayload)JsonTools.getNextObject(reader, false, typeof(MessagePayload));
                            content = CsChatClient.ChatClient.Instance().getContent(payload);
                        }
                        else if (reader.Value.Equals("direction"))
                        {
                            direction = (MessageDirection)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("to"))
                        {
                            toUsers = (List<string>)JsonTools.getNextObject(reader, false, typeof(List<string>));
                        } else if(reader.Value.Equals("status"))
                        {
                            status = (MessageStatus)JsonTools.getNextInt(reader);
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
