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
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_ADD_GROUP_MEMBER, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class AddGroupMemberNotificationContent : GroupNotificationMessageContent
    {
        public string invitor;
        public List<string> invitees;

        public override void decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                invitor = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                groupId = jo["g"].Value<string>();
            }

            if (jo["ms"] != null)
            {
                JArray jArray = jo["ms"].Value<JArray>();
                invitees = new List<string>();
                foreach(var jsonItem in jArray)
                {
                    invitees.Add(jsonItem.Value<string>());
                }
            }
        }

        public override string digest(MessageEx message)
        {
            return "Add group members";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (invitor != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(invitor);
            }

            if (groupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(groupId);
            }

            if(invitees != null && invitees.Count() > 0)
            {
                writer.WriteStartArray();

                foreach(var it in invitees)
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
