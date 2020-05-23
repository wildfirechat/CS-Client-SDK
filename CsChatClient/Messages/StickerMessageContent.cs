using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;
using System.Text;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_STICKER, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class StickerMessageContent : MediaMessageContent
    {
        public int Width { get; set; }
        public int Height { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);

            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["x"] != null)
            {
                Width = jo["x"].Value<int>();
            }

            if (jo["y"] != null)
            {
                Height = jo["y"].Value<int>();
            }
        }

        public override string Digest(MessageEx message)
        {
            return "[动态表情]";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();

            writer.WritePropertyName("x");
            writer.WriteValue(Width);

            writer.WritePropertyName("y");
            writer.WriteValue(Height);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.BinaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }
    }
}
