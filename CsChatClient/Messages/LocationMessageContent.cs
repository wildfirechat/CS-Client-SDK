using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_LOCATION, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class LocationMessageContent : MessageContent
    {
        public string title;
        public byte[] thumbnailData;
        public double lng;
        public double lat;

        public override void decode(MessagePayload payload)
        {
            thumbnailData = payload.binaryContent;
            title = payload.searchableContent;

            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.content);

            if (jo["lat"] != null)
            {
                lat = jo["lat"].Value<double>();
            }

            if (jo["long"] != null)
            {
                lng = jo["long"].Value<double>();
            }
        }

        public override string digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.searchableContent = title;
            payload.binaryContent = thumbnailData;


            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();


            writer.WritePropertyName("lat");
            writer.WriteValue(lat);

            writer.WritePropertyName("long");
            writer.WriteValue(lng);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.content = jsonText2;

            return payload;
        }
    }
}
