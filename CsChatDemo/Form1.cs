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

namespace CsChatDemo
{
    public partial class Form1 : Form, ConnectionStatusListener, ReceiveMessageListener, UserInfoUpdateListener, GroupInfoUpdateListener, GroupMemberUpdateListener, ContactUpdateListener, FriendRequestUpdateListener, UserSettingUpdateListener, ChannelInfoUpdateListener
    {
        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            ChatClient.Instance().disconnect();
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

            string clientId = ChatClient.Instance().getClientId();
            Console.WriteLine(clientId);

            ChatClient.Instance().setConnectionStatusListener(this);
            ChatClient.Instance().setReceiveMessageListener(this);
            ChatClient.Instance().setChannelInfoUpdateListener(this);
            ChatClient.Instance().setContactUpdateListener(this);
            ChatClient.Instance().setFriendRequestUpdateListener(this);
            ChatClient.Instance().setGroupInfoUpdateListener(this);
            ChatClient.Instance().setGroupMemberUpdateListener(this);
            ChatClient.Instance().setUserInfoUpdateListener(this);
            ChatClient.Instance().setUserSettingUpdateListener(this);

            string json = "{\"mobile\":\"" + phone + "\",\"code\":\"" + superCode + "\",\"clientId\":\"" + clientId + "\",\"platform\":3}";
            string responseJson = getToken(json);


            JObject jo = (JObject)JsonConvert.DeserializeObject(responseJson);
            if(jo["code"].Value<int>() == 0)
            {
                string userId = jo["result"]["userId"].Value<string>();
                string token = jo["result"]["token"].Value<string>();

                ChatClient.Instance().connect(userId, token);
            } else
            {
                appendLog("获取token失败!!!");
            }
        }

        private void testBtn_Click(object sender, EventArgs e)
        {
            if(!ChatClient.Instance().isLogined())
            {
                appendLog("没有登录，无法测试");
                return;
            }
            if(ChatClient.Instance().getConnectionStatus() != ConnectionStatus.kConnectionStatusConnected)
            {
                appendLog("不在已连接状态，无法测试");
                return;
            }

            appendLog("开始测试");

            string currentUserId = ChatClient.Instance().getCurrentUserId();
            appendLog("当前登录用户id是：" + currentUserId);

            UserInfo userInfo = ChatClient.Instance().getUserInfo(currentUserId, false);
            if(userInfo == null)
            {
                appendLog("当前登录用户信息为空，这可能是因为本地没有存储，协议栈会去服务器同步，同步后会通过用户信息更新回调来通知");
            } else {
                appendLog("当前登录用户名：" + userInfo.displayName);
            }
            

            Int64 deltaTime = ChatClient.Instance().getServerDeltaTime();
            appendLog("当前设备与服务器之间的时间差为:" + deltaTime);

            List<ConversationInfo> convs = ChatClient.Instance().getConversationInfos(new List<ConversationType>() { ConversationType.Single_Type, ConversationType.Group_Type, ConversationType.Channel_Type }, new List<int>() { 0 });
            appendLog("获取到 " + convs.Count() + " 条会话记录");

            Conversation conv = new Conversation(ConversationType.Single_Type, "cgc8c8VV", 0);

            ConversationInfo convInfo = ChatClient.Instance().getConversationInfo(conv);
            if(convInfo != null)
            {
                appendLog("获取到一个会话记录成功");
            } else
            {
                appendLog("获取到一个会话记录失败");
            }

            List<ConversationSearchInfo> searchConvs = ChatClient.Instance().searchConversation("hello", new List<ConversationType>() { ConversationType.Single_Type, ConversationType.Group_Type, ConversationType.Channel_Type }, new List<int>() { 0 });
            appendLog("搜索到了 " + searchConvs.Count() + " 条会话信息");

            ChatClient.Instance().removeConversation(conv, false);
            appendLog("移除会话信息");

            convInfo = ChatClient.Instance().getConversationInfo(conv);
            if (convInfo != null)
            {
                appendLog("获取到一个会话记录成功");
            }
            else
            {
                appendLog("获取到一个会话记录失败");
            }


            ChatClient.Instance().setConversationTop(conv, true, () => {
                appendLog("set conversation top success");
            }, (int errorCode) =>
            {
                appendLog("set conversation top failure " + errorCode);
            });

            FileMessageContent fileMsg = new FileMessageContent();
            fileMsg.localPath = "d:\\Debug.zip";

            TextMessageContent txt = new TextMessageContent();
            txt.content = "你好 world";

            ChatClient.Instance().sendMessage(conv, txt, null, 0, (long uid, long ts)=> {
                appendLog("send success");
            }, (int sended, int total)=> {
                appendLog("send progress:(" + total + ":" + sended + ")");
            }, (int errorcode)=> {
                appendLog("send failure");
            });
        }

        public void onConnectionStatusChanged(int status)
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

        public void onReceiveMessages(List<MessageEx> messages, bool hasMore)
        {
            Console.WriteLine("receive messages");
            foreach (var msg in messages)
            {
                UserInfo userInfo = ChatClient.Instance().getUserInfo(msg.sender, false);
                string line;
                if (userInfo == null)
                {
                    line = ":";
                }
                else
                {
                    line = userInfo.displayName + ":";
                }

                line += msg.content.digest(msg);
                appendLog(line);
            }
        }

        void ReceiveMessageListener.onRecallMessage(string operatorId, long messageUid)
        {
            Console.WriteLine("recall message");
            UserInfo userInfo = ChatClient.Instance().getUserInfo(operatorId, false);
            string line;
            if (userInfo == null)
            {
                line = ":";
            }
            else
            {
                line = userInfo.displayName + ":";
            }
            line += "recall a message";
            appendLog(line);
        }

        private void phoneText_TextChanged(object sender, EventArgs e)
        {

        }

        public void onUserInfoUpdated(List<UserInfo> userInfos)
        {
            string log = "User info of ";
            foreach(var ui in userInfos)
            {
                log = log + ui.displayName;
                log = log + " ";
            }
            log += "updated!";
            appendLog(log);
        }

        public void onContactUpdated(List<string> friendUids)
        {
            appendLog("friend list updated");
        }

        public void onFriendRequestUpdated()
        {
            appendLog("firnd request updated!");
        }

        public void onUserSettingUpdated()
        {
            appendLog("user setting updated");
        }

        public void onChannelInfoUpdated(List<ChannelInfo> channelInfos)
        {
            foreach(var channelInfo in channelInfos)
            {
                string line = "channel " + channelInfo.name + " updated!";
                appendLog(line);
            }
        }

        public void onGroupMemberUpdated(string groupId)
        {
            GroupInfo gi = ChatClient.Instance().getGroupInfo(groupId, false);
            if(gi != null)
            {
                string line = gi.name + " group member changed";
                appendLog(line);
            } else
            {
                appendLog("group member changed");
            }
        }

        public void onGroupInfoUpdated(List<GroupInfo> groupInfos)
        {
            string line = "group ";
            foreach(var g in groupInfos)
            {
                line += g.name;
                line += " ";
            }
            appendLog(line);
        }

        public void onDeleteMessage(long messageUid)
        {
            throw new NotImplementedException();
        }
    }
}
