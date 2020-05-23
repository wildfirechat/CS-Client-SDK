using System;
using System.Text;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MessageContentTypeRecall, MessageContentPersistFlag.PersistFlagPersist)]
    public class RecallMessageContent : NotificationMessageContent
    {
        public long MessageUid { get; set; }
        public string OperatorUser { get; set; }
        public string OriginalSender { get; set; }
        public int OriginalContentType { get; set; }
        public string OriginalSearchableContent { get; set; }
        public string OriginalContent { get; set; }
        public string OriginalExtra { get; set; }
        public long OriginalTimestamp { get; set; }
        public override void Decode(MessagePayload payload)
        {
            OperatorUser = payload.Content;
            MessageUid = long.Parse(Encoding.UTF8.GetString(payload.BinaryContent));
            if(payload.Extra != null)
            {
                JObject jo = (JObject)JsonConvert.DeserializeObject(payload.Extra);

                if(jo == null)
                {
                    return;
                }


                if (jo["s"] != null)
                {
                    OriginalSender = jo["s"].Value<string>();
                }

                if (jo["t"] != null)
                {
                    OriginalContentType = jo["t"].Value<int>();
                }

                if (jo["sc"] != null)
                {
                    OriginalSearchableContent = jo["sc"].Value<string>();
                }

                if (jo["c"] != null)
                {
                    OriginalContent = jo["c"].Value<string>();
                }

                if (jo["e"] != null)
                {
                    OriginalExtra = jo["e"].Value<string>();
                }

                if (jo["ts"] != null)
                {
                    OriginalTimestamp = jo["ts"].Value<long>();
                }
            }

        }

        public override string Digest(MessageEx message)
        {
            return "Recall message";
        }

        public override MessagePayload Encode()
        {
            //no need implement, client can't send recall message directly.
            return null;
        }

        public override string FormatNotification(MessageEx message)
        {
            return Digest(message);
        }
    }
}
