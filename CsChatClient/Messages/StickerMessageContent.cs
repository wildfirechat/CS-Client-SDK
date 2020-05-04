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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_STICKER, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class StickerMessageContent : MediaMessageContent
    {
        public int width;
        public int height;

        public override void decode(MessagePayload payload)
        {
            base.decode(payload);

            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["x"] != null)
            {
                width = jo["x"].Value<int>();
            }

            if (jo["y"] != null)
            {
                height = jo["y"].Value<int>();
            }
        }

        public override string digest(MessageEx message)
        {
            return "[动态表情]";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = base.encode();

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();

            writer.WritePropertyName("x");
            writer.WriteValue(width);

            writer.WritePropertyName("y");
            writer.WriteValue(height);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.binaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }
    }
}
