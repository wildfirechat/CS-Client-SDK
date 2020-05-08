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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_IMAGETEXT, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class ImageTextMessageContent : MessageContent
    {
        public string title;
        public string content;
        public string url;
        public byte[] thumbnailData;

        public override void decode(MessagePayload payload)
        {
            title = payload.searchableContent;
            thumbnailData = payload.binaryContent;
            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.content);

            if (jo["c"] != null)
            {
                content = jo["c"].Value<string>();
            }
            if(jo["u"] != null)
            {
                url = jo["u"].Value<string>();
            }
        }

        public override string digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.binaryContent = thumbnailData;
            payload.searchableContent = title;


            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();


            writer.WritePropertyName("c");
            writer.WriteValue(content);

            writer.WritePropertyName("u");
            writer.WriteValue(url);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.content = jsonText2;

            return payload;
        }
    }
}
