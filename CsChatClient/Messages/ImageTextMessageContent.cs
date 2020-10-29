using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Text;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeLink, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class ImageTextMessageContent : MessageContent
    {
        public string Title { get; set; }
        public string Content { get; set; }
        public string Url { get; set; }
        public string ThumbnailUrl { get; set; }

        public override void Decode(MessagePayload payload)
        {
            Title = payload.SearchableContent;

            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);
            if (jo != null)
            {
                if (jo["d"] != null)
                {
                    Content = jo["d"].Value<string>();
                }
                if (jo["u"] != null)
                {
                    Url = jo["u"].Value<string>();
                }
                if (jo["t"] != null)
                {
                    ThumbnailUrl = jo["t"].Value<string>();
                }
            }
            
        }

        public override string Digest(MessageEx message)
        {
            return "[Link]:" + Title;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.SearchableContent = Title;

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (Content != null)
            {
                writer.WritePropertyName("d");
                writer.WriteValue(Content);
            }

            if (Url != null)
            {
                writer.WritePropertyName("u");
                writer.WriteValue(Url);
            }

            if (ThumbnailUrl != null )
            {
                writer.WritePropertyName("t");
                writer.WriteValue(ThumbnailUrl);
            }

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.BinaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }
    }
}
