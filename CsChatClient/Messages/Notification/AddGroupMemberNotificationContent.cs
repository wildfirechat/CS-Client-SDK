using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_ADD_GROUP_MEMBER, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class AddGroupMemberNotificationContent : GroupNotificationMessageContent
    {
        public string Invitor { get; set; }
        public List<string> Invitees { get; set; }

        public override void Decode(MessagePayload payload)
        {
            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if (jo["o"] != null)
            {
                Invitor = jo["o"].Value<string>();
            }

            if (jo["g"] != null)
            {
                GroupId = jo["g"].Value<string>();
            }

            if (jo["ms"] != null)
            {
                JArray jArray = jo["ms"].Value<JArray>();
                Invitees = new List<string>();
                foreach(var jsonItem in jArray)
                {
                    Invitees.Add(jsonItem.Value<string>());
                }
            }
        }

        public override string Digest(MessageEx message)
        {
            return "Add group members";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if (Invitor != null)
            {
                writer.WritePropertyName("o");
                writer.WriteValue(Invitor);
            }

            if (GroupId != null)
            {
                writer.WritePropertyName("g");
                writer.WriteValue(GroupId);
            }

            if(Invitees != null && Invitees.Count() > 0)
            {
                writer.WriteStartArray();

                foreach(var it in Invitees)
                {
                    writer.WriteValue(it);
                }

                writer.WriteEndArray();
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
