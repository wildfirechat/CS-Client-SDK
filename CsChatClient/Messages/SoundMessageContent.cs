using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_SOUND, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class SoundMessageContent : MediaMessageContent
    {
        public int Duration { get; set; }

        public override void Decode(MessagePayload payload)
        {
            base.Decode(payload);

            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.Content);

            if (jo["duration"] != null)
            {
                Duration = jo["duration"].Value<int>();
            }
        }

        public override string Digest(MessageEx message)
        {
            return "[语音]";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = base.Encode();
            payload.SearchableContent = "[语音]";

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();

            writer.WritePropertyName("duration");
            writer.WriteValue(Duration);
           
            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.Content = jsonText2;

            return payload;
        }
    }
}
