using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.IO;
using System.Text;

namespace CsChatClient.Messages
{
    [ContentAttribute(MessageContentType.VoipContentTypeStart, MessageContentPersistFlag.PersistFlagPersistAndCount)]
    public class CallStartMessageContent : MessageContent
    {
        public string CallId { get; set; }
        public string TargetId { get; set; }
        public long ConnectTime { get; set; }
        public long EndTime { get; set; }
        public bool AudioOnly { get; set; }

        /// <summary>
        /// 0, UnKnown,
        /// 1, Busy,
        /// 2, SignalError,
        /// 3, Hangup,
        /// 4, MediaError,
        /// 5, RemoteHangup,
        /// 6, OpenCameraFailure,
        /// 7, Timeout,
        /// 8, AcceptByOtherClient
        /// </summary>
        public int Status { get; set; }

        public override void Decode(MessagePayload payload)
        {
            CallId = payload.Content;
            string json = Encoding.UTF8.GetString(payload.BinaryContent);
            JObject jo = (JObject)JsonConvert.DeserializeObject(json);

            if(jo["c"] != null)
            {
                ConnectTime = jo["c"].Value<long>();
            }
            if (jo["e"] != null)
            {
                EndTime = jo["e"].Value<long>();
            }
            if (jo["s"] != null)
            {
                Status = (int)jo["s"].Value<long>();
            }

            TargetId = jo["t"].Value<string>();
            if(jo["o"] != null) { 
                AudioOnly = jo["o"].Value<long>() > 0;
            }
        }

        public override string Digest(MessageEx message)
        {
            return AudioOnly ? "音频电话" : "视频电话";
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.Content = CallId;

            StringWriter sw = new StringWriter();
            JsonWriter writer = new JsonTextWriter(sw);
            writer.WriteStartObject();
            if(ConnectTime > 0) { 
                writer.WritePropertyName("c");
                writer.WriteValue(ConnectTime);
            }

            if (EndTime > 0)
            {
                writer.WritePropertyName("e");
                writer.WriteValue(EndTime);
            }

            if (Status > 0)
            {
                writer.WritePropertyName("s");
                writer.WriteValue(Status);
            }

            writer.WritePropertyName("t");
            writer.WriteValue(TargetId);

            writer.WritePropertyName("a");
            writer.WriteValue(AudioOnly ? 1 : 0);

            writer.WriteEndObject();
            writer.Flush();
            string jsonText2 = sw.GetStringBuilder().ToString();

            payload.BinaryContent = Encoding.UTF8.GetBytes(jsonText2);

            return payload;
        }
    }
}
