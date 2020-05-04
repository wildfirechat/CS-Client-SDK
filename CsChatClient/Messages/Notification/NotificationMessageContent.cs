using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages.Notification
{
    public abstract class NotificationMessageContent : MessageContent
    {
        public abstract string formatNotification(MessageEx message);
    }
}
