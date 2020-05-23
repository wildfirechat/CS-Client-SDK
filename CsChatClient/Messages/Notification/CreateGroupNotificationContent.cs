using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;
using System.Text;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MessageContentTypeCreateGroup, MessageContentPersistFlag.PersistFlagPersist)]
    public class CreateGroupNotificationContent : GroupNotificationMessageContent
    {
        public string OperateUser { get; set; }
        public string GroupName { get; set; }
        public override void Decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                OperateUser = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                GroupId = jo["g"].Value<string>();
            }

            if (jo["n"] != null)
            {
                GroupName = jo["n"].Value<string>();
            }
        }

        public override string Digest(MessageEx message)
        {
            return "Create group";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (OperateUser != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(OperateUser);
            }

            if (GroupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(GroupId);
            }

            if (GroupName != null)
            {
                writer.WritePropertyName("n");
                writer.WriteValue(GroupName);
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
