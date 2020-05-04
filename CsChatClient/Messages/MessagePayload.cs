using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace CsChatClient.Messages
{
    public class MessagePayload : Serializable
    {
        public /*MessageContentType*/ int contentType;
        public String searchableContent;
        public String pushContent;
        public String content;
        public byte[] binaryContent;

        public int mentionedType;
        public List<String> mentionedTargets;


        public MediaType mediaType;
        public String remoteMediaUrl;


        //前面的属性都会在网络发送，下面的属性只在本地存储
        public String localMediaPath;

        //前面的属性都会在网络发送，下面的属性只在本地存储
        public String localContent;
        public String extra;

        public void Serialize(JsonWriter writer)
        {
            writer.WriteStartObject();
            writer.WritePropertyName("contentType");
            writer.WriteValue(contentType);
            writer.WritePropertyName("searchableContent");
            writer.WriteValue(searchableContent);
            writer.WritePropertyName("pushContent");
            writer.WriteValue(pushContent);
            writer.WritePropertyName("content");
            writer.WriteValue(content);

            writer.WritePropertyName("binaryContent");
            string strContent = Convert.ToBase64String(binaryContent);
            //change base64 string to utf8 format after decode , i don't very sure
            writer.WriteValue(Encoding.UTF8.GetString(Encoding.UTF8.GetBytes(strContent)));

            writer.WritePropertyName("mentionedType");
            writer.WriteValue(mentionedType);
            writer.WritePropertyName("mentionedTargets");
            JsonTools.serializeList<string>(writer, mentionedTargets);
            writer.WritePropertyName("mediaType");
            writer.WriteValue((int)mediaType);
            writer.WritePropertyName("remoteMediaUrl");
            writer.WriteValue(remoteMediaUrl);
            writer.WritePropertyName("localMediaPath");
            writer.WriteValue(localMediaPath);
            writer.WritePropertyName("localContent");
            writer.WriteValue(localContent);
            writer.WritePropertyName("extra");
            writer.WriteValue(extra);

            writer.WriteEndObject();
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
                            contentType = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("searchableContent"))
                        {
                            searchableContent = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("pushContent"))
                        {
                            pushContent = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("content"))
                        {
                            content = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("binaryContent"))
                        {
                            var strContent = JsonTools.getNextString(reader);
                            //change base64 string to utf8 format before encode, i don't very sure
                            binaryContent = Convert.FromBase64String(Encoding.UTF8.GetString(Encoding.UTF8.GetBytes(strContent)));
                        }
                        else if (reader.Value.Equals("mentionedType"))
                        {
                            mentionedType = JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("mentionedTargets"))
                        {
                            mentionedTargets = (List<string>)JsonTools.getNextObject(reader, false, typeof(List<string>));
                        }
                        else if (reader.Value.Equals("mediaType"))
                        {
                            mediaType = (MediaType)JsonTools.getNextInt(reader);
                        }
                        else if (reader.Value.Equals("localContent"))
                        {
                            localContent = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("remoteMediaUrl"))
                        {
                            remoteMediaUrl = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("localMediaPath"))
                        {
                            localMediaPath = JsonTools.getNextString(reader);
                        }
                        else if (reader.Value.Equals("extra"))
                        {
                            extra = JsonTools.getNextString(reader);
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
