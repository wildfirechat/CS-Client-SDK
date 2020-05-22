using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_CHANGE_MUTE, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class GroupMuteNotificationContent : GroupNotificationMessageContent
    {
        public override void decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["c"] != null)
            {
                connectTime = jo["c"].Value<Int64>();
            }
        }

        public override string digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (connectTime > 0)
            {
                writer.WritePropertyName("c");
                writer.WriteValue(connectTime);
            }

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.binaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }

        public override string formatNotification(MessageEx message)
        {
            return digest(message);
        }
    }
}
