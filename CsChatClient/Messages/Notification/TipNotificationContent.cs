using System;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TIP, MessageContentPersistFlag.PersistFlag_PERSIST)]
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
