using System;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MessageContentTypeTip, MessageContentPersistFlag.PersistFlagPersist)]
    public class TipNotificationContent : NotificationMessageContent
    {
        public string Tip { get; set; }
        public override void Decode(MessagePayload payload)
        {
            Tip = payload.Content;
        }

        public override string Digest(MessageEx message)
        {
            return Tip;
        }

        public override MessagePayload Encode()
        {
            MessagePayload payload = new MessagePayload();
            payload.Content = Tip;
            return payload;
        }

        public override string FormatNotification(MessageEx message)
        {
            return Digest(message);
        }
    }
}
