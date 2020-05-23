using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_LOCATION, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class LocationMessageContent : MessageContent
    {
        public string Title { get; set; }
        public byte[] ThumbnailData { get; set; }
        public double Lng { get; set; }
        public double Lat { get; set; }

        public override void Decode(MessagePayload payload)
        {
            ThumbnailData = payload.BinaryContent;
            Title = payload.SearchableContent;

            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.Content);

            if (jo["lat"] != null)
            {
                Lat = jo["lat"].Value<double>();
            }

            if (jo["long"] != null)
            {
                Lng = jo["long"].Value<double>();
            }
        }

        public override string Digest(MessageEx message)
        {
            return "Location message";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.SearchableContent = Title;
            payload.BinaryContent = ThumbnailData;


            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();


            writer.WritePropertyName("lat");
            writer.WriteValue(Lat);

            writer.WritePropertyName("long");
            writer.WriteValue(Lng);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.Content = jsonText2;

            return payload;
        }
    }
}
