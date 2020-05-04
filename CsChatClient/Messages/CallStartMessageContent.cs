using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.VOIP_CONTENT_TYPE_START, MessageContentPersistFlag.PersistFlag_PERSIST_AND_COUNT)]
    class CallStartMessageContent : MessageContent
    {
        public String callId;
        public String targetId;
        public long connectTime;
        public long endTime;
        public bool audioOnly;

        /**
         * 0, UnKnown,
         * 1, Busy,
         * 2, SignalError,
         * 3, Hangup,
         * 4, MediaError,
         * 5, RemoteHangup,
         * 6, OpenCameraFailure,
         * 7, Timeout,
         * 8, AcceptByOtherClient
         */
        public int status;


        public override void decode(MessagePayload payload)
        {
            callId = payload.content;
            string json = Encoding.UTF8.GetString(payload.binaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if(jo["c"] != null)
            {
                connectTime = jo["c"].Value<Int64>();
            }
            if (jo["e"] != null)
            {
                endTime = jo["e"].Value<Int64>();
            }
            if (jo["s"] != null)
            {
                status = (int)jo["s"].Value<Int64>();
            }

            targetId = jo["t"].Value<string>();
            if(jo["o"] != null) { 
                audioOnly = jo["o"].Value<Int64>() > 0;
            }
        }

        public override string digest(MessageEx message)
        {
            return audioOnly ? "音频电话" : "视频电话";
        }

        public override MessagePayload encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.content = callId;

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if(connectTime > 0) { 
                writer.WritePropertyName("c");
                writer.WriteValue(connectTime);
            }

            if (endTime > 0)
            {
                writer.WritePropertyName("e");
                writer.WriteValue(endTime);
            }

            if (status > 0)
            {
                writer.WritePropertyName("s");
                writer.WriteValue(status);
            }

            writer.WritePropertyName("t");
            writer.WriteValue(targetId);

            writer.WritePropertyName("a");
            writer.WriteValue(audioOnly ? 1 : 0);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.binaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }
    }
}
