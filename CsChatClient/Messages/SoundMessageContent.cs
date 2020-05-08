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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_SOUND, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    public class SoundMessageContent : MediaMessageContent
    {
        public int duration;

        public override void decode(MessagePayload payload)
        {
            base.decode(payload);

            JObject jo = (JObject)JsonConvert.DeserializeObject(payload.content);

            if (jo["duration"] != null)
            {
                duration = jo["duration"].Value<int>();
            }
        }

        public override string digest(MessageEx message)
        {
            return "[语音]";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = base.encode();
            payload.searchableContent = "[语音]";

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();

            writer.WritePropertyName("duration");
            writer.WriteValue(duration);
           
            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();
            payload.content = jsonText2;

            return payload;
        }
    }
}
