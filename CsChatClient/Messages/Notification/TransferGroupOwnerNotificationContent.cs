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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TRANSFER_GROUP_OWNER, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class TransferGroupOwnerNotificationContent : GroupNotificationMessageContent
    {
        public string operateUser;
        public string owner;
        public override void decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                operateUser = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                groupId = jo["g"].Value<string>();
            }

            if (jo["m"] != null)
            {
                owner = jo["m"].Value<string>();
            }
        }

        public override string digest(MessageEx message)
        {
            return "Transfer group";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (operateUser != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(operateUser);
            }

            if (groupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(groupId);
            }

            if (owner != null)
            {
                writer.WritePropertyName("m");
                writer.WriteValue(owner);
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
