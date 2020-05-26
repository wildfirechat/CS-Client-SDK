using System;
using System.Collections.Generic;
using System.Text;
using Newtonsoft.Json;

namespace CsChatClient.Messages
{
    public class MessagePayload : ISerializable
    {
        /// <summary>
        /// MessageContentType
        /// </summary>
        public int ContentType { get; set; }
        public string SearchableContent { get; set; }
        public string PushContent { get; set; }
        public string Content { get; set; }
        public byte[] BinaryContent { get; set; }

        public int MentionedType { get; set; }
        public List<string> MentionedTargets { get; set; }


        public MediaType MediaType { get; set; }
        public string RemoteMediaUrl { get; set; }

        //前面的属性都会在网络发送，下面的属性只在本地存储
        public string LocalMediaPath { get; set; }

        //前面的属性都会在网络发送，下面的属性只在本地存储
        public string LocalContent { get; set; }
        public string Extra { get; set; }

        public void Serialize(JsonWriter writer)
        {
            writer.WriteStartObject();
            writer.WritePropertyName("type");
            writer.WriteValue(ContentType);
            writer.WritePropertyName("searchableContent");
            writer.WriteValue(SearchableContent);
            writer.WritePropertyName("pushContent");
            writer.WriteValue(PushContent);
            writer.WritePropertyName("content");
            writer.WriteValue(Content);

            writer.WritePropertyName("binaryContent");
            if(BinaryContent != null)
            {
                string strContent = Convert.ToBase64String(BinaryContent);
                //change base64 string to utf8 format after decode , i don't very sure
                writer.WriteValue(Encoding.UTF8.GetString(Encoding.UTF8.GetBytes(strContent)));
            } else
            {
                writer.WriteValue("");
            }
            

            writer.WritePropertyName("mentionedType");
            writer.WriteValue(MentionedType);
            writer.WritePropertyName("mentionedTargets");
            JsonTools.SerializeList<string>(writer, MentionedTargets);
            writer.WritePropertyName("mediaType");
            writer.WriteValue((int)MediaType);
            writer.WritePropertyName("remoteMediaUrl");
            writer.WriteValue(RemoteMediaUrl);
            writer.WritePropertyName("localMediaPath");
            writer.WriteValue(LocalMediaPath);
            writer.WritePropertyName("localContent");
            writer.WriteValue(LocalContent);
            writer.WritePropertyName("extra");
            writer.WriteValue(Extra);

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
                            ContentType = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("searchableContent"))
                        {
                            SearchableContent = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("pushContent"))
                        {
                            PushContent = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("content"))
                        {
                            Content = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("binaryContent"))
                        {
                            var strContent = JsonTools.GetNextString(reader);
                            //change base64 string to utf8 format before encode, i don't very sure
                            BinaryContent = Convert.FromBase64String(Encoding.UTF8.GetString(Encoding.UTF8.GetBytes(strContent)));
                        }
                        else if (reader.Value.Equals("mentionedType"))
                        {
                            MentionedType = JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("mentionedTargets"))
                        {
                            MentionedTargets = (List<string>)JsonTools.GetNextObject(reader, false, typeof(List<string>));
                        }
                        else if (reader.Value.Equals("mediaType"))
                        {
                            MediaType = (MediaType)JsonTools.GetNextInt(reader);
                        }
                        else if (reader.Value.Equals("localContent"))
                        {
                            LocalContent = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("remoteMediaUrl"))
                        {
                            RemoteMediaUrl = JsonTools.GetNextString(reader);
                        }
                        else if (reader.Value.Equals("localMediaPath"))
                        {
                            LocalMediaPath = JsonTools.GetNextString(reader);
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
