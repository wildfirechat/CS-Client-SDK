using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_RECALL, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class RecallMessageContent : NotificationMessageContent
    {
        public long messageUid;
        public string operatorUser;
        public string originalSender;
        public int originalContentType;
        public string originalSearchableContent;
        public string originalContent;
        public string originalExtra;
        public long originalTimestamp;
        public override void decode(MessagePayload payload)
        {
            operatorUser = payload.content;
            messageUid = long.Parse(Encoding.UTF8.GetString(payload.binaryContent));
            if(payload.extra != null)
            {
                JObject jo = (JObject)JsonConvert.DeserializeObject(payload.extra);

                if (jo["s"] != null)
                {
                    originalSender = jo["s"].Value<string>();
                }

                if (jo["t"] != null)
                {
                    originalContentType = jo["t"].Value<int>();
                }

                if (jo["sc"] != null)
                {
                    originalSearchableContent = jo["sc"].Value<string>();
                }

                if (jo["c"] != null)
                {
                    originalContent = jo["c"].Value<string>();
                }

                if (jo["e"] != null)
                {
                    originalExtra = jo["e"].Value<string>();
                }

                if (jo["ts"] != null)
                {
                    originalTimestamp = jo["ts"].Value<long>();
                }
            }

        }

        public override string digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload encode()
        {
            //no need implement, client can't send recall message directly.
            return null;
        }

        public override string formatNotification(MessageEx message)
        {
            return digest(message);
        }
    }
}
