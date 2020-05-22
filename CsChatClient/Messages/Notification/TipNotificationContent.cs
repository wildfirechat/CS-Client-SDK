using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsChatClient.Messages.Notification
{
    [ContentAttribute(MessageContentType.MESSAGE_CONTENT_TYPE_TIP, MessageContentPersistFlag.PersistFlag_PERSIST)]
    public class TipNotificationContent : NotificationMessageContent
    {
        public override void decode(MessagePayload payload)
        {
            throw new NotImplementedException();
        }

        public override string digest(MessageEx message)
        {
            throw new NotImplementedException();
        }

        public override MessagePayload encode()
        {
            throw new NotImplementedException();
        }

        public override string formatNotification(MessageEx message)
        {
            return digest(message);
        }
    }
}
