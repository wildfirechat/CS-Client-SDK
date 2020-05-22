using System;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TIP, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class TipNotificationContent : NotificationMessageContent
    {
        public override void Decode(MessagePayload payload)
        {
            throw new NotImplementedException();
        }

        public override string Digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload Encode()
        {
            throw new NotImplementedException();
        }

        public override string FormatNotification(MessageEx message)
        {
            return Digest(message);
        }
    }
}
