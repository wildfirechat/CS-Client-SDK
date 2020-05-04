using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages.Notification
{
    public abstract class GroupNotificationMessageContent : NotificationMessageContent
    {
        public string groupId;
        public long connectTime;
    }
}
