using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;
using System.Text;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_QUIT_GROUP, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class QuitGroupNotificationContent : GroupNotificationMessageContent
    {
        public string QuitMember { get; set; }
        public override void Decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                QuitMember = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                GroupId = jo["g"].Value<string>();
            }
        }

        public override string Digest(MessageEx message)
        {
            return "Quit group";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (QuitMember != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(QuitMember);
            }

            if (GroupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(GroupId);
            }

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.BinaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }

        public override string FormatNotification(MessageEx message)
        {
            return Digest(message);
        }
    }
}
