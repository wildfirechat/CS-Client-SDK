namespace CsChatClient.Messages.Notification
{
    public abstract class NotificationMessageContent : MessageContent
    {
        public abstract string FormatNotification(MessageEx message);
    }
}
