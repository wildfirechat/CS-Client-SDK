using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CsChatClient;
using CsChatClient.Messages;
using CsChatClient.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using CsChatClient.Messages.Notification;

namespace CsChatDemo
{
    public partial class Form1 : Form, IConnectionStatusListener, IReceiveMessageListener, IUserInfoUpdateListener, IGroupInfoUpdateListener, IGroupMemberUpdateListener, IContactUpdateListener, IFriendRequestUpdateListener, IUserSettingUpdateListener, IChannelInfoUpdateListener
    {
        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            ChatClient.Instance().Disconnect();
            base.OnFormClosing(e);
        }

        private void connectBtn_Click(object sender, EventArgs e)
        {
            string phone = phoneText.Text;
            string superCode = superCodeText.Text;
            if(phone.Length == 0 || superCode.Length == 0)
            {
                return;
            }

            string clientId = ChatClient.Instance().GetClientId();
            Console.WriteLine(clientId);

            ChatClient.Instance().SetConnectionStatusListener(this);
            ChatClient.Instance().SetReceiveMessageListener(this);
            ChatClient.Instance().SetChannelInfoUpdateListener(this);
            ChatClient.Instance().SetContactUpdateListener(this);
            ChatClient.Instance().SetFriendRequestUpdateListener(this);
            ChatClient.Instance().SetGroupInfoUpdateListener(this);
            ChatClient.Instance().SetGroupMemberUpdateListener(this);
            ChatClient.Instance().SetUserInfoUpdateListener(this);
            ChatClient.Instance().SetUserSettingUpdateListener(this);

            string json = "{\"mobile\":\"" + phone + "\",\"code\":\"" + superCode + "\",\"clientId\":\"" + clientId + "\",\"platform\":3}";
            string responseJson = getToken(json);


            JObject jo = (JObject)JsonConvert.DeserializeObject(responseJson);
            if(jo["code"].Value<int>() == 0)
            {
                string userId = jo["result"]["userId"].Value<string>();
                string token = jo["result"]["token"].Value<string>();

                ChatClient.Instance().Connect(userId, token);
            } else
            {
                appendLog("获取token失败!!!");
            }
        }

        private void testBtn_Click(object sender, EventArgs e)
        {
            if(!ChatClient.Instance().IsLogined())
            {
                appendLog("没有登录，无法测试");
                return;
            }
            if(ChatClient.Instance().GetConnectionStatus() != ConnectionStatus.KConnectionStatusConnected)
            {
                appendLog("不在已连接状态，无法测试");
                return;
            }

            appendLog("开始测试");

            string currentUserId = ChatClient.Instance().GetCurrentUserId();
            appendLog("当前登录用户id是：" + currentUserId);

            UserInfo userInfo = ChatClient.Instance().GetUserInfo(currentUserId, false);
            if(userInfo == null)
            {
                appendLog("当前登录用户信息为空，这可能是因为本地没有存储，协议栈会去服务器同步，同步后会通过用户信息更新回调来通知");
            } else {
                appendLog("当前登录用户名：" + userInfo.DisplayName);
            }
            

            Int64 deltaTime = ChatClient.Instance().GetServerDeltaTime();
            appendLog("当前设备与服务器之间的时间差为:" + deltaTime);

            List<ConversationInfo> convs = ChatClient.Instance().GetConversationInfos(new List<ConversationType>() { ConversationType.SingleType, ConversationType.GroupType, ConversationType.ChannelType }, new List<int>() { 0 });
            appendLog("获取到 " + convs.Count() + " 条会话记录");

            Conversation conv = new Conversation(ConversationType.SingleType, "cgc8c8VV", 0);

            ConversationInfo convInfo = ChatClient.Instance().GetConversationInfo(conv);
            if(convInfo != null)
            {
                appendLog("获取到一个会话记录成功");
            } else
            {
                appendLog("获取到一个会话记录失败");
            }

            List<ConversationSearchInfo> searchConvs = ChatClient.Instance().SearchConversation("hello", new List<ConversationType>() { ConversationType.SingleType, ConversationType.GroupType, ConversationType.ChannelType }, new List<int>() { 0 });
            appendLog("搜索到了 " + searchConvs.Count() + " 条会话信息");

            ChatClient.Instance().RemoveConversation(conv, false);
            appendLog("移除会话信息");

            convInfo = ChatClient.Instance().GetConversationInfo(conv);
            if (convInfo != null)
            {
                appendLog("获取到一个会话记录成功");
            }
            else
            {
                appendLog("获取到一个会话记录失败");
            }


            ChatClient.Instance().SetConversationTop(conv, true, () => {
                appendLog("set conversation top success");
            }, (int errorCode) =>
            {
                appendLog("set conversation top failure " + errorCode);
            });

            FileMessageContent fileMsg = new FileMessageContent();
            fileMsg.LocalPath = "d:\\Debug.zip";

            TextMessageContent txt = new TextMessageContent();
            txt.Content = "你好 world";

            ChatClient.Instance().SendMessage(conv, txt, null, 0, (long uid, long ts)=> {
                appendLog("send success");
            }, (int sended, int total)=> {
                appendLog("send progress:(" + total + ":" + sended + ")");
            }, (int errorcode)=> {
                appendLog("send failure");
            });
        }

        public void OnConnectionStatusChanged(int status)
        {
            Console.WriteLine("status is " + status);
            string str = "Connect status changed to " + status;
            appendLog(str);
        }

        public string getToken(string jsonParam)
        {
            string _url = "http://wildfirechat.cn:8888/login";
            //json参数
            //string jsonParam = "{ phonenumber:\"18665885202\",pwd:\"tsp\"}";
            var request = (HttpWebRequest)WebRequest.Create(_url);
            request.Method = "POST";
            request.ContentType = "application/json;charset=UTF-8";
            byte[] byteData = Encoding.UTF8.GetBytes(jsonParam);
            int length = byteData.Length;
            request.ContentLength = length;
            Stream writer = request.GetRequestStream();
            writer.Write(byteData, 0, length);
            writer.Close();
            var response = (HttpWebResponse)request.GetResponse();
            var responseString = new StreamReader(response.GetResponseStream(), Encoding.GetEncoding("utf-8")).ReadToEnd();
            return responseString;
        }

        public delegate void AppendLogInvokeCallback(string log);
        private void appendLog(string log)
        {
            if(InvokeRequired)
            {
                Invoke(new AppendLogInvokeCallback(appendLog), log);
            } else
            {
                logLabel.Text = log + "\n" + logLabel.Text;
            }
        }

        public void OnReceiveMessages(List<MessageEx> messages, bool hasMore)
        {
            Console.WriteLine("receive messages");
            foreach (var msg in messages)
            {
                UserInfo userInfo = ChatClient.Instance().GetUserInfo(msg.Sender, false);
                string line;
                if (userInfo == null)
                {
                    line = ":";
                }
                else
                {
                    line = userInfo.DisplayName + ":";
                }

                line += msg.Content.Digest(msg);
                appendLog(line);
            }
        }

        void IReceiveMessageListener.OnRecallMessage(long messageUid)
        {
            Console.WriteLine("recall message");
            RecallMessageContent recall = (RecallMessageContent)ChatClient.Instance().GetMessageByUid(messageUid).Content;
            UserInfo userInfo = ChatClient.Instance().GetUserInfo(recall.OperatorUser, false);
            string line;
            if (userInfo == null)
            {
                line = ":";
            }
            else
            {
                line = userInfo.DisplayName + ":";
            }
            line += "recall a message";
            appendLog(line);
        }

        private void phoneText_TextChanged(object sender, EventArgs e)
        {

        }

        public void OnUserInfoUpdated(List<UserInfo> userInfos)
        {
            string log = "User info of ";
            foreach(var ui in userInfos)
            {
                log = log + ui.DisplayName;
                log = log + " ";
            }
            log += "updated!";
            appendLog(log);
        }

        public void OnContactUpdated(List<string> friendUids)
        {
            appendLog("friend list updated");
        }

        public void OnFriendRequestUpdated()
        {
            appendLog("firnd request updated!");
        }

        public void OnUserSettingUpdated()
        {
            appendLog("user setting updated");
        }

        public void OnChannelInfoUpdated(List<ChannelInfo> channelInfos)
        {
            foreach(var channelInfo in channelInfos)
            {
                string line = "channel " + channelInfo.Name + " updated!";
                appendLog(line);
            }
        }

        public void OnGroupMemberUpdated(string groupId)
        {
            GroupInfo gi = ChatClient.Instance().GetGroupInfo(groupId, false);
            if(gi != null)
            {
                string line = gi.Name + " group member changed";
                appendLog(line);
            } else
            {
                appendLog("group member changed");
            }
        }

        public void OnGroupInfoUpdated(List<GroupInfo> groupInfos)
        {
            string line = "group ";
            foreach(var g in groupInfos)
            {
                line += g.Name;
                line += " ";
            }
            appendLog(line);
        }

        public void OnDeleteMessage(long messageUid)
        {
            throw new NotImplementedException();
        }
    }
}
