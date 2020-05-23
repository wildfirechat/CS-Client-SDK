using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MessageContentTypeImagetext, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class ImageTextMessageContent : MessageContent
    {
        public string Title { get; set; }
        public string Content { get; set; }
        public string Url { get; set; }
        public byte[] ThumbnailData { get; set; }

        public override void Decode(MessagePayload payload)
        {
            Title = payload.SearchableContent;
            ThumbnailData = payload.BinaryContent;
            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.Content);

            if (jo["c"] != null)
            {
                Content = jo["c"].Value<string>();
            }
            if(jo["u"] != null)
            {
                Url = jo["u"].Value<string>();
            }
        }

        public override string Digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.BinaryContent = ThumbnailData;
            payload.SearchableContent = Title;


            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();


            writer.WritePropertyName("c");
            writer.WriteValue(Content);

            writer.WritePropertyName("u");
            writer.WriteValue(Url);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.Content = jsonText2;

            return payload;
        }
    }
}
