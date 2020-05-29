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
    [ContentAttribute(MessageContentType.MessageContentTypeMuteGroupMember, MessageContentPersistFlag.PersistFlagPersist)]
    public class MuteGroupMemberNotification : GroupNotificationMessageContent
    {
        public string OperateUser { get; set; }
        public string Type { get; set; }
        public List<string> MemberIds { get; set; }
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
                Type = jo["n"].Value<string>();
            }

            if (jo["ms"] != null)
            {
                JArray jArray = jo["ms"].Value<JArray>();
                MemberIds = new List<string>();
                foreach (var jsonItem in jArray)
                {
                    MemberIds.Add(jsonItem.Value<string>());
                }
            }
        }

        public override string Digest(MessageEx message)
        {
            return "Mute group members";
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

            if (Type != null)
            {
                writer.WritePropertyName("n");
                writer.WriteValue(Type);
            }

            if (MemberIds != null && MemberIds.Count() > 0)
            {
                writer.WriteStartArray();

                foreach (var it in MemberIds)
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
