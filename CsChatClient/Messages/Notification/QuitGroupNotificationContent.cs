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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_QUIT_GROUP, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class QuitGroupNotificationContent : GroupNotificationMessageContent
    {
        public string quitMember;
        public override void decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                quitMember = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                groupId = jo["g"].Value<string>();
            }
        }

        public override string digest(MessageEx message)
        {
            return "Quit group";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (quitMember != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(quitMember);
            }

            if (groupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(groupId);
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
