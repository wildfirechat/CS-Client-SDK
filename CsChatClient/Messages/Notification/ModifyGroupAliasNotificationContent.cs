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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_MODIFY_GROUP_ALIAS, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class ModifyGroupAliasNotificationContent : GroupNotificationMessageContent
    {
        public string operateUser;
        public string alias;
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

            if (jo["n"] != null)
            {
                alias = jo["n"].Value<string>();
            }
        }

        public override string digest(MessageEx message)
        {
            return "Modify group member alias";
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

            if (alias != null)
            {
                writer.WritePropertyName("n");
                writer.WriteValue(alias);
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
