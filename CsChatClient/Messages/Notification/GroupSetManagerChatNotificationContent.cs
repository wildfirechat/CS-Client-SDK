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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_SET_MANAGER, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class GroupSetManagerChatNotificationContent : GroupNotificationMessageContent
    {
        public string operateUser;
        public string type;
        public List<string> memberIds;
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
                type = jo["n"].Value<string>();
            }

            if (jo["ms"] != null)
            {
                JArray jArray = jo["ms"].Value<JArray>();
                memberIds = new List<string>();
                foreach (var jsonItem in jArray)
                {
                    memberIds.Add(jsonItem.Value<string>());
                }
            }
        }

        public override string digest(MessageEx message)
        {
            return "Group set group managers";
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

            if (type != null)
            {
                writer.WritePropertyName("n");
                writer.WriteValue(type);
            }

            if (memberIds != null && memberIds.Count() > 0)
            {
                writer.WriteStartArray();

                foreach (var it in memberIds)
                {
                    writer.WriteValue(it);
                }

                writer.WriteEndArray();
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
