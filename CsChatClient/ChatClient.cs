using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ClrChatClient;
using CsChatClient.Messages;
using CsChatClient.Models;
using System.Reflection;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;

namespace CsChatClient
{

    /*
    全局状态监听，建议程序启动时设置
    */

    /*
     连接状态监听
     */
    public interface ConnectionStatusListener
    {
        void onConnectionStatusChanged(int status);
    }


    /*
     消息监听
     */
    public interface ReceiveMessageListener
    {
        void onReceiveMessages(List<MessageEx> messages, bool hasMore);
        void onRecallMessage(string operatorId, Int64 messageUid);
        void onDeleteMessage(Int64 messageUid);
    };

    /*
     用户信息变更监听
     */
    public interface UserInfoUpdateListener
    {
        void onUserInfoUpdated(List<UserInfo> userInfos);
    };

    /*
    群组信息变更监听
    */
    public interface GroupInfoUpdateListener
    {
        void onGroupInfoUpdated(List<GroupInfo> groupInfos);
    };

    /*
    群组成员变更监听
    */
    public interface GroupMemberUpdateListener
    {
        void onGroupMemberUpdated(string groupId);
    };

    /*
     联系人状态监听
     */
    public interface ContactUpdateListener
    {
        void onContactUpdated(List<string> friendUids);
    };

    /*
     好友请求状态变更坚挺
     */
    public interface FriendRequestUpdateListener
    {
        void onFriendRequestUpdated();
    };

    /*
     用户设置监听
     */
    public interface UserSettingUpdateListener
    {
        void onUserSettingUpdated();
    };

    /*
     频道信息变更监听
     */
    public interface ChannelInfoUpdateListener
    {
        void onChannelInfoUpdated(List<ChannelInfo> channelInfos);
    };


    /**
     事件回调，一般都是一次性的。
     */

    /*
     通用的void的事件回调
     */
    public interface GeneralVoidCallback
    {
        void onSuccess();
        void onFailure(int errorCode);
    };

    /*
    通用的string的事件回调
    */
    public interface GeneralStringCallback
    {
        void onSuccess(string value);
        void onFailure(int errorCode);
    };

    /*
     获取远程历史消息回调
     */
    public interface GetRemoteMessageCallback
    {
        void onSuccess(List<MessageEx> messages);
        void onFailure(int errorCode);
    };

    /*
     发送消息回调
     */
    public interface WFSendMessageCallback
    {
        void onSuccess(Int64 messageUid, Int64 timestamp);
        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void onProgress(int uploaded, int total);
        void onFailure(int errorCode);
    };

    /*
     搜索用户回调
     */
    public interface SearchUserCallback
    {
        void onSuccess(List<UserInfo> messages);
        void onFailure(int errorCode);
    };

    /*
     获取聊天室信息回调
     */
    public interface GetChatroomInfoCallback
    {
        void onSuccess(ChatroomInfo chatroomInfo);
        void onFailure(int errorCode);
    };

    /*
     获取聊天室成员信息回调
     */
    public interface GetChatroomMemberInfoCallback
    {
        void onSuccess(ChatroomMemberInfo chatroomMemberInfo);
        void onFailure(int errorCode);
    };

    /*
     获取频道信息回调
     */
    public interface GetChannelInfoCallback
    {
        void onSuccess(ChannelInfo channelInfo);
        void onFailure(int errorCode);
    };

    /*
     搜索频道回调
     */
    public interface SearchChannelCallback
    {
        void onSuccess(List<ChannelInfo> channels);
        void onFailure(int errorCode);
    };

    /*
     上传媒体文件回调
     */
    public interface UploadMediaCallback
    {
        void onSuccess(string remoteUrl);
        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void onProgress(int uploaded, int total);
        void onFailure(int errorCode);
    };

    /**
 会话类型

 - Single_Type: 单聊
 - Group_Type: 群组
 - Chatroom_Type: 聊天室
 - Channel_Type: 频道
 */
    public enum ConversationType
    {
        Single_Type,
        Group_Type,
        Chatroom_Type,
        Channel_Type,
    };

    /**
搜索用户类型

- SearchUserType_General: 模糊搜索diaplayName，精确匹配name和电话
- SearchUserType_Name_Mobile: 精确匹配name和电话
- SearchUserType_Name: 精确匹配name
- SearchUserType_Mobile: 精确匹配电话
*/
    public enum SearchUserType
    {
        SearchUserType_General,
        SearchUserType_Name_Mobile,
        SearchUserType_Name,
        SearchUserType_Mobile
    };

    /**
群組类型

- GroupType_Normal: 微信风格群组
- GroupType_Free: 自由风格
- GroupType_Restricted: 带有群管理的群，建议用这个
*/

    public enum GroupType
    {
        GroupType_Normal,
        GroupType_Free,
        GroupType_Restricted,
    };

    /**
     群成員類型
     * 
     * */
    public enum GroupMemberType
    {
        Normal,
        Manager,
        Owner,
        Silent,
        Removed
    };

    
    public enum UserSettingScope
    {
        kUserSettingConversationSilent = 1,
        kUserSettingGlobalSilent = 2,
        kUserSettingConversationTop = 3,
        kUserSettingHiddenNotificationDetail = 4,
        kUserSettinGroupHideNickname = 5,
        kUserSettingFavouriteGroup = 6,
        kUserSettingConversationSync = 7,
        kUserSettingMyChannels = 8,
        kUserSettingListenedChannels = 9,

        kUserSettingCustomBegin = 1000
    };

    /**
     修改个人信息的内容

     - Modify_DisplayName: 修改显示名
     - Modify_Portrait: 修改头像
     - Modify_Gender: 修改性别
     - Modify_Mobile: 修改手机号
     - Modify_Email: 修改邮箱
     - Modify_Address: 修改地址
     - Modify_Company: 修改公司信息
     - Modify_Social: 修改社交信息
     - Modify_Extra: 修改扩展信息
     */
    public enum ModifyMyInfoType
    {
        Modify_DisplayName = 0,
        Modify_Portrait = 1,
        Modify_Gender = 2,
        Modify_Mobile = 3,
        Modify_Email = 4,
        Modify_Address = 5,
        Modify_Company = 6,
        Modify_Social = 7,
        Modify_Extra = 8
    };

    public enum ModifyGroupInfoType
    {
        Modify_Group_Name = 0,
        Modify_Group_Portrait = 1,
        Modify_Group_Extra = 2,
        Modify_Group_Mute = 3,
        Modify_Group_JoinType = 4,
        Modify_Group_PrivateChat = 5,
        Modify_Group_Searchable = 6
    };


    public enum ModifyChannelInfoType
    {
        Modify_Channel_Name = 0,
        Modify_Channel_Portrait = 1,
        Modify_Channel_Desc = 2,
        Modify_Channel_Extra = 3,
        Modify_Channel_Secret = 4,
        Modify_Channel_Callback = 5
    };

    /**
     媒体类型

     - Media_Type_GENERAL: 一般
     - Media_Type_IMAGE: 图片
     - Media_Type_VOICE: 语音
     - Media_Type_VIDEO: 视频
     - Media_Type_File: 文件
     - Media_Type_PORTRAIT: 头像
     - Media_Type_FAVORITE: 收藏
     */
    public enum MediaType
    {
        Media_Type_GENERAL = 0,
        Media_Type_IMAGE = 1,
        Media_Type_VOICE = 2,
        Media_Type_VIDEO = 3,
        Media_Type_File = 4,
        Media_Type_PORTRAIT = 5,
        Media_Type_FAVORITE = 6
    };

    /**
     连接状态

     - kConnectionStatusSecretKeyMismatch 密钥错误
     - kConnectionStatusTokenIncorrect Token错误
     - kConnectionStatusServerDown 服务器关闭
     - kConnectionStatusRejected: 被拒绝
     - kConnectionStatusLogout: 退出登录
     - kConnectionStatusUnconnected: 未连接
     - kConnectionStatusConnecting: 连接中
     - kConnectionStatusConnected: 已连接
     - kConnectionStatusReceiving: 获取离线消息中，可忽略
     */
    public enum ConnectionStatus
    {
        kConnectionStatusSecretKeyMismatch = -6,
        kConnectionStatusTokenIncorrect = -5,
        kConnectionStatusServerDown = -4,
        kConnectionStatusRejected = -3,
        kConnectionStatusLogout = -2,
        kConnectionStatusUnconnected = -1,
        kConnectionStatusConnecting = 0,
        kConnectionStatusConnected = 1,
        kConnectionStatusReceiving = 2
    };

    /**
     正在输入类型
     
     - Typing_TEXT : 正在输入文本
     - Typing_VOICE : 正在输入语音
     - Typing_CAMERA : 正在拍摄
     - Typing_LOCATION : 正在选取位置
     - Typing_FILE : 正在选取文件
     */
    public enum TypingType
    {
        Typing_TEXT = 0,
        Typing_VOICE = 1,
        Typing_CAMERA = 2,
        Typing_LOCATION = 3,
        Typing_FILE = 4
    };

    /**
     消息方向
     
     - Direction_Send : 当前用户发送的消息
     - Direction_Receive : 当前用户接收的消息
     */
    public enum MessageDirection
    {
        Direction_Send = 0,
        Direction_Receive = 1
    };

    public enum MessageContentType
    {
        /*
         * 说明：1000以下为系统保留类型，自定义消息请使用1000以上数值。
         * 系统消息类型中100以下为常用基本类型消息。100-199位群组消息类型。400-499为VoIP消息类型.
         */
        //基本消息类型
        //未知类型的消息
        MESSAGE_CONTENT_TYPE_UNKNOWN = 0,
        //文本消息
        MESSAGE_CONTENT_TYPE_TEXT = 1,
        //语音消息
        MESSAGE_CONTENT_TYPE_SOUND = 2,
        //图片消息
        MESSAGE_CONTENT_TYPE_IMAGE = 3,
        //位置消息
        MESSAGE_CONTENT_TYPE_LOCATION = 4,
        //文件消息
        MESSAGE_CONTENT_TYPE_FILE = 5,
        //视频消息
        MESSAGE_CONTENT_TYPE_VIDEO = 6,
        //动态表情消息
        MESSAGE_CONTENT_TYPE_STICKER = 7,
        //图文消息
        MESSAGE_CONTENT_TYPE_IMAGETEXT = 8,
        //存储不计数文本消息
        MESSAGE_CONTENT_TYPE_P_TEXT = 9,


        //撤回消息
        MESSAGE_CONTENT_TYPE_RECALL = 80,

        //提醒消息
        MESSAGE_CONTENT_TYPE_TIP = 90,

        //正在输入消息
        MESSAGE_CONTENT_TYPE_TYPING = 91,

        //通知消息类型
        //创建群的通知消息
        MESSAGE_CONTENT_TYPE_CREATE_GROUP = 104,
        //加群的通知消息
        MESSAGE_CONTENT_TYPE_ADD_GROUP_MEMBER = 105,
        //踢出群成员的通知消息
        MESSAGE_CONTENT_TYPE_KICKOF_GROUP_MEMBER = 106,
        //退群的通知消息
        MESSAGE_CONTENT_TYPE_QUIT_GROUP = 107,
        //解散群的通知消息
        MESSAGE_CONTENT_TYPE_DISMISS_GROUP = 108,
        //转让群主的通知消息
        MESSAGE_CONTENT_TYPE_TRANSFER_GROUP_OWNER = 109,
        //修改群名称的通知消息
        MESSAGE_CONTENT_TYPE_CHANGE_GROUP_NAME = 110,
        //修改群昵称的通知消息
        MESSAGE_CONTENT_TYPE_MODIFY_GROUP_ALIAS = 111,
        //修改群头像的通知消息
        MESSAGE_CONTENT_TYPE_CHANGE_GROUP_PORTRAIT = 112,

        MESSAGE_CONTENT_TYPE_CHANGE_MUTE = 113,
        MESSAGE_CONTENT_TYPE_CHANGE_JOINTYPE = 114,
        MESSAGE_CONTENT_TYPE_CHANGE_PRIVATECHAT = 115,
        MESSAGE_CONTENT_TYPE_CHANGE_SEARCHABLE = 116,
        MESSAGE_CONTENT_TYPE_SET_MANAGER = 117,

        //VoIP开始消息
        VOIP_CONTENT_TYPE_START = 400,
    };

    /**
     消息存储类型
     
     - NOT_PERSIST: 本地不存储
     - PERSIST: 本地存储
     - PERSIST_AND_COUNT: 本地存储，并计入未读计数
     - TRANSPARENT: 透传消息，不多端同步，如果对端不在线，消息会丢弃
     */
    public enum MessageContentPersistFlag
    {
        PersistFlag_NOT_PERSIST = 0,
        PersistFlag_PERSIST = 1,
        PersistFlag_PERSIST_AND_COUNT = 3,
        PersistFlag_TRANSPARENT = 4,
    };

    public enum MessageStatus
    {
        Message_Status_Sending,
        Message_Status_Sent,
        Message_Status_Send_Failure,
        Message_Status_Mentioned,
        Message_Status_AllMentioned,
        Message_Status_Unread,
        Message_Status_Readed,
        Message_Status_Played
    };

    public class ChatClient
    {
        static public ChatClient Instance() { return INSTANCE; }
        

        /**
     设置连接状态监听，在connect之前调用

     @param listener 连接回调监听
     */
        public void setConnectionStatusListener(ConnectionStatusListener listener) { PROTO.setConnectStatusListener(listener.onConnectionStatusChanged); }


        /**
        设置接受消息监听，在connect之前调用

        @param listener 监听
        */
        public void setReceiveMessageListener(ReceiveMessageListener listener) {
            PROTO.setMessageListener(new ReceiveMessageWrapper(listener).onReceive, listener.onRecallMessage, listener.onDeleteMessage);
        }


        /**
        设置用戶信息變更监听，在connect之前调用

        @param listener 监听
        */
        public void setUserInfoUpdateListener(UserInfoUpdateListener listener)
        {
            PROTO.setUserInfoUpdateListener(new UserInfoUpdateWrapper(listener).onUserInfoUpdated);
        }

        /**
        设置群組信息變更监听，在connect之前调用

        @param listener 监听
        */
        public void setGroupInfoUpdateListener(GroupInfoUpdateListener listener)
        {
            PROTO.setGroupInfoUpdateListener(new GroupInfoUpdateWrapper(listener).onGroupInfoUpdated); 
        }

        /**
        设置群組成員信息變更监听，在connect之前调用

        @param listener 监听
        */
        public void setGroupMemberUpdateListener(GroupMemberUpdateListener listener)
        {
            PROTO.setGroupMemberUpdateListener(listener.onGroupMemberUpdated);
        }

        /**
        设置聯係人狀態變更监听，在connect之前调用

        @param listener 监听
        */
        public void setContactUpdateListener(ContactUpdateListener listener)
        {
            PROTO.setContactUpdateListener(new ContactUpdateWrapper(listener).onContactUpdated);
        }

        /**
        设置好友請求變更监听，在connect之前调用

        @param listener 监听
        */
        public void setFriendRequestUpdateListener(FriendRequestUpdateListener listener)
        {
            PROTO.setFriendRequestUpdateListener(listener.onFriendRequestUpdated);
        }

        /**
        设置設置监听，在connect之前调用

        @param listener 监听
        */
        public void setUserSettingUpdateListener(UserSettingUpdateListener listener)
        {
            PROTO.setUserSettingUpdateListener(listener.onUserSettingUpdated);
        }

        /**
        设置頻道信息更新监听，在connect之前调用

        @param listener 监听
        */
        public void setChannelInfoUpdateListener(ChannelInfoUpdateListener listener)
        {
            PROTO.setChannelInfoUpdateListener(new ChannelInfoUpdateWrapper(listener).onChannelInfoUpdated);
        }

        /**
        设置自定义消息元宵，在connect之前调用，实现方法请参考文本文件

        @param prototype 自定义消息原型
        */
        public void registerMessage(Type type)
        {
            ContentAttribute attribute = (ContentAttribute)Attribute.GetCustomAttribute(type, typeof(ContentAttribute));
            if(attribute != null)
            {
                MessageContentTypeDict[attribute.type] = type;
                PROTO.registerMessageFlag(attribute.type, (int)attribute.flag);
            }
        }

        /**
         获取当前设备的设备Id
         */
        public string getClientId() { return PROTO.getClientId(); }

        /**
         连接IM服务。注意必须getClientId函数获取当前机器的id，然后使用clientId获取token，不然将会连接失败。程序結束前需要調用disconnect。

         @param userId 用户Id
         @param token 用户令牌
         */
        public bool connect(string userId, string token)
        {
            registerMessage(typeof(TextMessageContent));
            registerMessage(typeof(CallStartMessageContent));
            return PROTO.connect(userId, token);
        }

        /**
        斷開連接
        */
        public void disconnect()
        {
            PROTO.disconnect();
        }
        /**
         当前是否已经调用connect
         */
        public bool isLogined()
        {
            return PROTO.isLogined();
        }

        /**
         获取当前连接状态
         */
        public ConnectionStatus getConnectionStatus()
        {
            return (ConnectionStatus)PROTO.getConnectionStatus();
        }

        /**
         获取当前登录用户的用户Id
         */
        public string getCurrentUserId()
        {
            return PROTO.getCurrentUserId();
        }

        /**
        获取本地时间与服务器时间的差值，精确度不高。
         */
        public Int64 getServerDeltaTime()
        {
            return PROTO.getServerDeltaTime();
        }


        /**
         获取会话信息

         @param conversationTypes 会话类型
         @param lines 默认传 @[@(0)]
         @return 会话信息
         */
        public List<ConversationInfo> getConversationInfos(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach(var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            string infoStr = PROTO.getConversationInfos(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationInfo> cs = JsonConvert.DeserializeObject<List<ConversationInfo>>(infoStr, convert);
            return cs;
        }


        /**
         获取会话信息

         @param conversation 会话
         @return 会话信息
         */
        public ConversationInfo getConversationInfo(Conversation conversation)
        {
            string info = PROTO.getConversationInfo((int)conversation.type, conversation.target, conversation.line);

            WfcJsonConverter convert = new WfcJsonConverter();
            ConversationInfo ci = JsonConvert.DeserializeObject<ConversationInfo>(info, convert);
            return ci;
        }

        /**
         搜索会话

         @param keyword 关键词
         @param conversationTypes 会话类型
         @param lines 默认传 @[@(0)]
         @return 会话搜索结果信息
         */
        public List<ConversationSearchInfo> searchConversation(string keyword, List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            string infos = PROTO.searchConversation(keyword, types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationSearchInfo> cs = JsonConvert.DeserializeObject<List<ConversationSearchInfo>>(infos, convert);
            return cs;
        }

        /**
         删除会话

         @param conversation 会话
         @param clearMessage 是否删除会话中的消息
         */
        public void removeConversation(Conversation conversation,bool clearMessage)
        {
            PROTO.removeConversation((int)conversation.type, conversation.target, conversation.line, clearMessage);
        }

        /**
         设置或取消会话置顶

         @param conversation 会话
         @param top 是否置顶
         @param callback 结果回调
         */
        public void setConversationTop(Conversation conversation, bool top, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setConversationTop((int)conversation.type, conversation.target, conversation.line, top, () => {
                succDele();
            }, (int errorCode) => {
                errDele(errorCode);
            });
        }

        /**
         设置会话免打扰

         @param conversation 会话
         @param silent 是否免打扰
         @param callback 结果回调
         */
        public void setConversationSilent(Conversation conversation, bool silent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setConversationSilent((int)conversation.type, conversation.target, conversation.line, silent, () => {
                succDele();
            }, (int errorCode) => {
                errDele(errorCode);
            });
        }

        /**
         设置会话草稿

         @param conversation 会话
         @param draft 草稿
         */
        public void setConversationDraft(Conversation conversation, string draft)
        {
            PROTO.setConversationDraft((int)conversation.type, conversation.target, conversation.line, draft);
        }

        /**
         获取指定类型会话的未读数

         @param conversationTypes 会话类型
         @param lines 默认传 @[@(0)]
         @return 未读数
         */
        public UnreadCount getUnreadCount(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            string unreadStr = PROTO.getUnreadCount(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /**
         获取某个会话的未读数

         @param conversation 会话
         @return 未读数
         */
        public UnreadCount getUnreadCount(Conversation conversation)
        {
            string unreadStr = PROTO.getUnreadCount((int)conversation.type, conversation.target, conversation.line);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /**
         清空会话未读数

         @param conversation 会话
         */
        public void clearUnreadStatus(Conversation conversation)
        {
            PROTO.clearUnreadStatus((int)conversation.type, conversation.target, conversation.line);
        }

        /**
        清空会话类型的未读数

        @param conversationTypes 会话类型
        @param lines 默认传 @[@(0)]
        */
        public void clearUnreadStatus(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            PROTO.clearUnreadStatus(types, lines);
        }

        /**
         清空所有会话的未读数
         */
        public  void clearAllUnreadStatus()
        {
            PROTO.clearAllUnreadStatus();
        }

        /**
         设置媒体消息已播放

         @param messageId 消息ID
         */
        public  void setMediaMessagePlayed(long messageId)
        {
            PROTO.setMediaMessagePlayed((int)messageId);
        }

        /**
         获取消息
         @discuss 获取从fromIndex起count条旧的消息。如果想要获取比fromIndex新的消息，count传负值。

         @param conversation 会话
         @param contentTypes 消息类型
         @param fromIndex 起始index
         @param count 总数
         @return 消息实体
         */
        public  List<MessageEx> getMessages(Conversation conversation, List<int> contentTypes, Int64 fromIndex,int count, string user)
        {
            string messagesStr = PROTO.getMessages((int)conversation.type, conversation.target, conversation.line, contentTypes, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /**
         获取某类会话信息

         @param conversationTypes 会话类型
         @param lines 默认传 @[@(0)]
         @param contentTypes 消息类型
         @param fromIndex 起始index
         @param count 总数
         @return 消息实体
         */
        public List<MessageEx> getMessages(List<ConversationType> conversationTypes, List<int> lines, List<int> contentTypes, Int64 fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            string messagesStr = PROTO.getMessages(types, lines, contentTypes, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /**
         获取某类会话信息

         @param conversationTypes 会话类型
         @param lines 默认传 @[@(0)]
         @param messageStatus 消息状态
         @param fromIndex 起始index
         @param count 总数
         @return 消息实体
         */
        public List<MessageEx> getMessages(List<ConversationType> conversationTypes, List<int> lines, MessageStatus messageStatus, Int64 fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }
            string messagesStr = PROTO.getMessages(types, lines, (int)messageStatus, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /**
         获取服务器消息

         @param conversation 会话
         @param beforeMessageUid 起始index
         @param count 总数
         @param callback 结果回调
         */
        public void getRemoteMessages(Conversation conversation, Int64 beforeMessageUid, int count, onGetRemoteMessageDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getRemoteMessages((int)conversation.type, conversation.target, conversation.line, beforeMessageUid, count, (string messages) =>
            {
                WfcJsonConverter convert = new WfcJsonConverter();
                List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messages, convert);
                succDele(ms);
            }, (int errorCode) =>
            {
                errDele(errorCode);
            });
        }
        /**
         获取消息

         @param messageId 消息ID
         @return 消息实体
         */
        public  MessageEx getMessage(long messageId)
        {
            string messageStr = PROTO.getMessage((int)messageId);

            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /**
         获取消息

         @param messageUid 消息UID
         @return 消息实体
         */
        public  MessageEx getMessageByUid(Int64 messageUid)
        {
            string messageStr = PROTO.getMessageByUid(messageUid);

            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /**
         搜索消息

         @param conversation 会话
         @param keyword 关键词
         @param count 数量
         @return 命中的消息
         */
        public  List<MessageEx> searchMessage(Conversation conversation, string keyword, int count)
        {
            string messagesStr = PROTO.searchMessage((int)conversation.type, conversation.target, conversation.line, keyword, count);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /**
         发送消息

         @param conversation 会话
         @param content 消息内容
         @param toUsers 在会话中只发给该用户，如果为空则发到会话中
         @param expireDuration 消息的有效期，0不限期，单位秒
         @param callback 发送结果回调
         @return 消息实体
         */
        public MessageEx sendMessage(Conversation conversation, MessageContent content, List<string> toUsers, int expireDuration, onBigIntBigIntCallbackDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = PROTO.sendMessage((int)conversation.type, conversation.target, conversation.line, contentStr, toUsers, expireDuration, succDele, progressDele, errDele);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }
        /**
         撤回消息

         @param messageUid 待撤回的消息Uid
         @param callback 结果的回调

         @discuss 服务器不检查可撤回时间，应用逻辑来处理。
         */
        public void recallMessage(Int64 messageUid, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.recallMessage(messageUid, succDele, errDele);
        }

        /**
         上传媒体(图片、语音、文件等)

         @param fileName 文件名，可为空
         @param mediaData 媒体信息
         @param mediaType 媒体类型
         @param callback 回调
         */
        public void uploadMedia(string fileName, string mediaData, MediaType mediaType, onUploadedMediaDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            PROTO.uploadMedia(fileName, mediaData, (int)mediaType, (string remoteUrl) =>
            {
                succDele(remoteUrl);
            }, progressDele, errDele);
        }

        /**
         删除消息

         @param messageId 消息ID
         @return 是否删除成功
         */
        public bool deleteMessage(long messageId)
        {
            return PROTO.deleteMessage((int)messageId);
        }

        /**
         删除会话中的消息

         @param conversation 会话
         */
        public void clearMessages(Conversation conversation)
        {
            PROTO.clearMessages((int)conversation.type, conversation.target, conversation.line);
        }

        /**
         删除会话中的before之前的旧消息。

         @param conversation 会话，如果conversation为nil，则清除所有会话的消息。
         @param before 时间点，单位是毫秒
         */
        public void clearMessages(Conversation conversation, Int64 before)
        {
            PROTO.clearMessages((int)conversation.type, conversation.target, conversation.line, before);
        }

        /**
         插入消息

         @param conversation 会话
         @param content 消息内容
         @param status 消息状态，注意消息状态会影响消息方向
         @param serverTime 时间，0为当前时间
         @return 消息实体
         */
        public MessageEx insertMessage(Conversation conversation, string sender, MessageContent content, MessageStatus status, bool notify, Int64 serverTime)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = PROTO.insert((int)conversation.type, conversation.target, conversation.line, sender, contentStr, (int)status, notify, serverTime);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /**
         更新消息内容

         @param messageId 消息ID
         @param content 消息内容
         */
        public void updateMessage(long messageId, MessageContent content)
        {
            var contentStr = JsonTools.Stringfy(content);
            PROTO.updateMessage((int)messageId, contentStr);
        }

        /**
         获取用户信息

         @param userId 用户ID
         @param refresh 是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。
         @return 本地的用户信息，可能为空
         */
        public UserInfo getUserInfo(string userId, bool refresh)
        {
            string userStr = PROTO.getUserInfo(userId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            UserInfo ui = JsonConvert.DeserializeObject<UserInfo>(userStr, convert);
            return ui;
        }

        /**
         获取用户信息
         @discussion 获取用户信息，如果在群中有群昵称也一并返回

         @param userId 用户ID
         @param groupId 群组ID
         @param refresh 是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。
         @return 本地的用户信息，可能为空
         */
        public UserInfo getUserInfo(string userId, string groupId, bool refresh)
        {
            string userStr = PROTO.getUserInfo(userId, groupId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            UserInfo ui = JsonConvert.DeserializeObject<UserInfo>(userStr, convert);
            return ui;
        }

        /**
         批量获取用户信息

         @param userIds 用户ID列表
         @param groupId 群组ID
         @return 本地的用户信息列表。本地不存在的用户会返回只有id的用户信息，同时会拉取。
         */
        public List<UserInfo> getUserInfos(List< string > userIds, string groupId)
        {
            string usersStr = PROTO.getUserInfos(userIds, groupId);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
            return us;
        }

        /**
         搜索用户

         @param keyword 关键词
         @param searchType 搜索类型
         @param page page
         @param callback 回调
         */
        public void searchUser(string keyword, SearchUserType searchType, int page, onSearchUsersDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.searchUser(keyword, (int)searchType, page, (string usersStr) =>
            {
                WfcJsonConverter convert = new WfcJsonConverter();
                List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
                succDele(us);
            }, errDele);
        }

        /**
         查询用户和当前用户是否是好友关系

         @param userId 用户ID
         @return 是否是好友
         */
        public bool isMyFriend(string userId)
        {
            return PROTO.isMyFriend(userId);
        }

        /**
         获取当前用户的好友列表

         @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
         @return 好友列表的用户ID
         */
        public List<string> getMyFriendList(bool refresh)
        {
            string friendsStr = PROTO.getMyFriendList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }


        /**
         搜索好友
         @param keyword 关键词
         @return 好友用户信息
         */
        public List<UserInfo> searchFriends(string keyword)
        {
            string usersStr = PROTO.searchFriends(keyword);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
            return us;
        }

        /**
         搜索群组
         @param keyword 关键词
         @return 群组搜索结果
         */
        public List<GroupSearchInfo> searchGroups(string keyword)
        {
            string usersStr = PROTO.searchGroups(keyword);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<GroupSearchInfo> gs = JsonConvert.DeserializeObject<List<GroupSearchInfo>>(usersStr, convert);
            return gs;
        }

        /**
         获取收到的好友请求

         @return 好友请求
         */
        public List<FriendRequest> getIncommingFriendRequest()
        {
            string usersStr = PROTO.getIncommingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /**
         获取发出的好友请求

         @return 好友请求
         */
        public List<FriendRequest> getOutgoingFriendRequest()
        {
            string usersStr = PROTO.getOutgoingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /**
         从服务器更新好友请求
         */
        public void loadFriendRequestFromRemote()
        {
            PROTO.loadFriendRequestFromRemote();
        }

        /**
         获取未读的好友请求数

         @return 未读的好友请求数
         */
        public int getUnreadFriendRequestStatus()
        {
            return PROTO.getUnreadFriendRequestStatus();
        }

        /**
         清除好友请求的未读数
         */
        public void clearUnreadFriendRequestStatus()
        {
            PROTO.clearUnreadFriendRequestStatus();
        }

        /**
         删除好友

         @param userId 用户ID
         @param callback 回调
         */
        public void deleteFriend(string userId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.deleteFriend(userId, succDele, errDele);
        }

        /**
         发送好友请求

         @param userId 用户ID
         @param reason 请求说明
         @param callback 回调
         */
        public void sendFriendRequest(string userId, string reason, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.sendFriendRequest(userId, reason, succDele, errDele);
        }

        /**
         处理好友请求

         @param userId 用户ID
         @param accpet 是否接受
         @param friendExtra extra
         @param callback 回调
         */
        public void handleFriendRequest(string userId, bool accpet, string friendExtra, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.handleFriendRequest(userId, accpet, friendExtra, succDele, errDele);
        }

        /**
        获取用户的别名

        @param userId 用户ID
        */
        public string getFriendAlias(string userId)
        {
            return PROTO.getFriendAlias(userId);
        }

        /**
        设置用户的别名

        @param userId 用户ID
        @param alias 别名
        @param callback 回调
        */
        public void setFriendAlias(string userId, string alias, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setFriendAlias(userId, alias, succDele, errDele);
        }

        /**
         查询用户是否被加入黑名单

         @param userId 用户ID
         @return 是否被加入黑名单
         */
        public bool isBlackListed(string userId)
        {
            return PROTO.isBlackListed(userId);
        }

        /**
         获取当前用户的黑名单列表

         @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
         @return 黑名单列表的用户ID
         */
        public List<string> getBlackList(bool refresh)
        {
            string friendsStr = PROTO.getBlackList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }

        /**
         设置黑名单

         @param userId 用户ID
         @param isBlackListed YES 加入黑名单； NO 取消黑名单
         @param callback 回调
         */
        public void setBlackList(string userId, bool isBlackListed, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setBlackList(userId, isBlackListed, succDele, errDele);
        }

        /**
         获取群成员信息

         @param groupId 群ID
         @param forceUpdate 是否强制从服务器更新，如果不刷新则从本地缓存中读取
         @return 群成员信息
         */
        public List<GroupMember> getGroupMembers(string groupId, bool forceUpdate)
        {
            string membersStr = PROTO.getGroupMembers(groupId, forceUpdate);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<GroupMember> us = JsonConvert.DeserializeObject<List<GroupMember>>(membersStr, convert);
            return us;
        }

        /**
         获取群信息

         @param groupId 群ID
         @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
         @return 群信息
         */
        public GroupInfo getGroupInfo(string groupId, bool refresh)
        {
            string gStr = PROTO.getGroupInfo(groupId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            GroupInfo us = JsonConvert.DeserializeObject<GroupInfo>(gStr, convert);
            return us;
        }

        /**
         获取群成员信息

         @param groupId 群ID
         @param memberId 群成员ID
         @return 群成员信息
         */
        public GroupMember getGroupMember(string groupId, string memberId)
        {
            string memberStr = PROTO.getGroupMember(groupId, memberId);
            WfcJsonConverter convert = new WfcJsonConverter();
            GroupMember us = JsonConvert.DeserializeObject<GroupMember>(memberStr, convert);
            return us;
        }

        /**
         创建群

         @param groupId 群ID,傳空時自動生成群組id，建議爲空
         @param groupName 群名称
         @param groupPortrait 群头像
         @param groupMembers 群成员
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void createGroup(string groupId, string groupName, string groupPortrait, GroupType type, List<string> groupMembers, List<int> notifyLines, MessageContent notifyContent, onCreateGroupDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.createGroup(groupId, groupName, groupPortrait, (int)type, groupMembers, notifyLines, contentStr, (string gid) =>
            {
                succDele(gid);
            }, errDele);
        }

        /**
         添加群成员

         @param members 成员的用户ID列表
         @param groupId 群ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void addMembers(List<string> members, string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.addMembers(members, groupId, notifyLines, contentStr, succDele, errDele);
        }

        /**
         踢出群成员

         @param members 成员的用户ID列表
         @param groupId 群ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void kickoffMembers(List<string> members, string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.kickoffMembers(members, groupId, notifyLines, contentStr, succDele, errDele);
        }

        /**
         退群

         @param groupId 群ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void quitGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.quitGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /**
         解散群

         @param groupId 群ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void dismissGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.dismissGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /**
         修改群信息

         @param groupId 群ID
         @param type    要修改的群属性
         @param newValue    要修改的群属性值
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void modifyGroupInfo(string groupId, ModifyGroupInfoType type, string newValue, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.modifyGroupInfo(groupId, (int)type, newValue, notifyLines, contentStr, succDele, errDele);
        }

        /**
         修改群昵称

         @param groupId 群ID
         @param newAlias 昵称
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void modifyGroupAlias(string groupId, string newAlias, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.modifyGroupAlias(groupId, newAlias, notifyLines, contentStr, succDele, errDele);
        }

        /**
         转移群主

         @param groupId 群ID
         @param newOwner 群主的用户ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void transferGroup(string groupId, string newOwner, List<int> notifyLines, MessageContent notifyContent,  onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.transferGroup(groupId, newOwner, notifyLines, contentStr, succDele, errDele);
        }

        /**
         设置群管理

         @param groupId 群ID
         @param isSet    设置或取消
         @param memberId    成员ID
         @param notifyLines 默认传 @[@(0)]
         @param notifyContent 通知消息
         @param callback 回调
         */
        public void setGroupManager(string groupId, bool isSet, List<string> memberIds, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.setGroupManager(groupId, isSet, memberIds, notifyLines, contentStr, succDele, errDele);
        }

        /**
         获取当前用户收藏的群组

         @return 当前用户收藏的群组ID
         */
        public List<string> getFavGroups()
        {
            string membersStr = PROTO.getFavGroups();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /**
         是否是当前用户收藏的群组

         @return 是否是当前用户收藏的群组
         */
        public bool isFavGroup(string groupId)
        {
            return PROTO.isFavGroup(groupId);
        }

        /**
         设置群组收藏状态

         @param groupId 群组ID
         @param fav 是否收藏
         @param callback 回调
         */
        public void setFavGroup(string groupId, bool fav, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setFavGroup(groupId, fav, succDele, errDele);
        }

        /**
         获取个人设置

         @param scope 设置项的scope
         @param key 设置项的key
         @return 设置值
         */
        public string getUserSetting(UserSettingScope scope, string key)
        {
            return PROTO.getUserSetting((int)scope, key);
        }

        /**
         获取个人一类设置

         @param scope 设置项的scope
         @return scope对应的所有设置值
         */
        public Dictionary<string, string> getUserSettings(UserSettingScope scope)
        {
            return null;
        }

        /**
         设置个人设置项

         @param scope 设置项的scope
         @param key 设置项的key
         @param value 值
         @param callback 成功的回调
         */
        public void setUserSetting(UserSettingScope scope, string key, string value, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setUserSetting((int)scope, key, value, succDele, errDele);
        }

        /**
         修改个人信息

         @param values 信息
         @param callback 成功的回调

         @discuss 性别属性是int类型，修改时需要转为字符串类型
         */
        public void modifyMyInfo(Dictionary<int, string> values, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.modifyMyInfo(values, succDele, errDele);
        }

        /**
         是否是全局禁止通知
        */
        public bool isGlobalSlient()
        {
            return PROTO.isGlobalSlient();
        }

        /**
         设置全局禁止通知

         @param slient 是否禁止通知
         @param callback 回调
         */
        public void setGlobalSlient(bool slient, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setGlobalSlient(slient, succDele, errDele);
        }

        /**
        通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
        */
        public bool isHiddenNotificationDetail()
        {
            return PROTO.isHiddenNotificationDetail();
        }

        /**
        设置通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”

        @param hidden 是否隐藏详情
        @param callback 回调
        */
        public void setHiddenNotificationDetail(bool hidden, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setHiddenNotificationDetail(hidden, succDele, errDele);
        }

        /**
        群聊中是否显示群成员名称

        @param hidden 是否显示
        @param groupId 群组ID
        @param callback 回调
        */
        public void setHiddenGroupMemberName(bool hidden, string groupId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setHiddenGroupMemberName(hidden, groupId, succDele, errDele);
        }


        /**
        加入聊天室

        @param chatroomId 聊天室ID
        @param callback 回调
        */
        public void joinChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.joinChatroom(chatroomId, succDele, errDele);
        }

        /**
        退出聊天室

        @param chatroomId 聊天室ID
        @param callback 回调
        */
        public void quitChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.quitChatroom(chatroomId, succDele, errDele);
        }

        /**
        获取聊天室信息

        @param chatroomId 聊天室ID
        @param updateDt 上次聊天室获取时间戳，可以为0
        @param callback 回调
        */
        public void getChatroomInfo(string chatroomId, Int64 updateDt, onGetChatroomInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getChatroomInfo(chatroomId, updateDt, (string str) =>
            {
                ChatroomInfo chatroomInfo = JsonTools.Jsonfy<ChatroomInfo>(str);
                succDele(chatroomInfo);
            }, errDele);
        }

        /**
        获取聊天室成员信息

        @param chatroomId 聊天室ID
        @param maxCount 最大成员数量，建议不超过100
        @param callback 回调
        */
        public void getChatroomMemberInfo(string chatroomId, int maxCount, onGetChatroomMemberInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getChatroomMemberInfo(chatroomId, maxCount, (string str) =>
            {
                ChatroomMemberInfo memberInfo = JsonTools.Jsonfy<ChatroomMemberInfo>(str);
            }, errDele);
        }

        /**
         创建频道

         @param channelName 频道名称
         @param channelPortrait 频道头像
         @param status 频道状态，这里使用0
         @param desc 频道描述
         @param extra 频道extra
         @param callback 回调
         */
        public void createChannel(string channelName, string channelPortrait, int status, string desc, string extra, onGeneralStringSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.createChannel(channelName, channelPortrait, status, desc, extra, succDele, errDele);
        }

        /**
         获取频道信息

         @param channelId 频道ID
         @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
         @return 群信息
         */
        public ChannelInfo getChannelInfo(string channelId, bool refresh)
        {
            string str = PROTO.getChannelInfo(channelId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            ChannelInfo us = JsonConvert.DeserializeObject<ChannelInfo>(str, convert);
            return us;
        }

        /**
         修改频道信息

         @param channelId 群ID
         @param type    要修改的群属性
         @param newValue    要修改的群属性值
         @param callback 回调
         */
        public void modifyChannelInfo(string channelId, ModifyChannelInfoType type, string newValue, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.modifyChannelInfo(channelId, (int)type, newValue, succDele, errDele);
        }

        /**
         搜索频道

         @param keyword 关键词
         @param callback 回调
         */
        public void searchChannel(string keyword, onSearchChannelsDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.searchChannel(keyword, (string str) =>
            {
                List<ChannelInfo> channels = JsonTools.Jsonfy<List<ChannelInfo>>(str);
                succDele(channels);
            }, errDele);
        }

        /**
         是否收听频道

         @param channelId 频道ID
         @return YES，收听；NO，未收听
         */
        public bool isListenedChannel(string channelId)
        {
            return PROTO.isListenedChannel(channelId);
        }

        /**
         收听或者取消收听频道

         @param channelId 频道ID
         @param listen 是否收听
         @param callback 回调
         */
        public void listenChannel(string channelId, bool listen, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.listenChannel(channelId, listen, succDele, errDele);
        }

        /**
         获取当前用户创建的频道

         @return 当前用户创建的频道ID
         */
        public List<string> getMyChannels()
        {
            string membersStr = PROTO.getMyChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /**
         获取当前用户收听的频道

         @return 当前用户收听的频道ID
         */
        public List<string> getListenedChannels()
        {
            string membersStr = PROTO.getListenedChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /**
         销毁频道

         @param channelId 频道ID
         @param callback 回调
         */
        public void destoryChannel(string channelId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.destoryChannel(channelId, succDele, errDele);
        }


        class ReceiveMessageWrapper
        {
            public ReceiveMessageWrapper(ReceiveMessageListener listener) { m_listener = listener; }
            private ReceiveMessageListener m_listener;

            public void onReceive(string messages, bool hasMore)
            {
                List<MessageEx> ms = JsonTools.Jsonfy<List<MessageEx>>(messages);
                m_listener.onReceiveMessages(ms, hasMore);
            }
        }

        class UserInfoUpdateWrapper
        {
            public UserInfoUpdateWrapper(UserInfoUpdateListener listener) { m_listener = listener; }
            private UserInfoUpdateListener m_listener;

            public void onUserInfoUpdated(string users)
            {
                List<UserInfo> userInfos = JsonTools.Jsonfy<List<UserInfo>>(users);
                m_listener.onUserInfoUpdated(userInfos);
            }
        }

        class GroupInfoUpdateWrapper
        {
            public GroupInfoUpdateWrapper(GroupInfoUpdateListener listener) { m_listener = listener; }
            private GroupInfoUpdateListener m_listener;

            public void onGroupInfoUpdated(string groups)
            {
                List<GroupInfo> groupInfos = JsonTools.Jsonfy<List<GroupInfo>>(groups);
                m_listener.onGroupInfoUpdated(groupInfos);
            }
        }

        class ContactUpdateWrapper
        {
            public ContactUpdateWrapper(ContactUpdateListener listener) { m_listener = listener; }
            private ContactUpdateListener m_listener;

            public void onContactUpdated(string groups)
            {
                List<string> friends = JsonTools.Jsonfy<List<string>>(groups);
                m_listener.onContactUpdated(friends);
            }
        }
        class ChannelInfoUpdateWrapper
        {
            public ChannelInfoUpdateWrapper(ChannelInfoUpdateListener listener) { m_listener = listener; }
            private ChannelInfoUpdateListener m_listener;

            public void onChannelInfoUpdated(string groups)
            {
                List< ChannelInfo> groupInfos = JsonTools.Jsonfy<List<ChannelInfo>>(groups);
                m_listener.onChannelInfoUpdated(groupInfos);
            }
        }


        
            
        




        public MessageContent getContent(MessagePayload payload)
        {
            
            MessageContent content;
            if (MessageContentTypeDict.ContainsKey(payload.contentType))
            {
                Type type = MessageContentTypeDict[payload.contentType];
                content = (MessageContent)Activator.CreateInstance(type);
                
            } else
            {
                content = new UnknownMessageContent();
            }

            content.decode(payload);
            return content;
        }

        private Proto PROTO = new Proto();
        private static ChatClient INSTANCE = new ChatClient();
        private Dictionary<int, Type> MessageContentTypeDict = new Dictionary<int, Type>();
    }

    public delegate void onGetRemoteMessageDelegate(List<MessageEx> messages);
    public delegate void onUploadedMediaDelegate(string remoteUrl);
    public delegate void onSearchUsersDelegate(List<UserInfo> users);
    public delegate void onCreateGroupDelegate(string groupId);
    public delegate void onGetChatroomInfoDelegate(ChatroomInfo chatroomInfo);
    public delegate void onGetChatroomMemberInfoDelegate(ChatroomMemberInfo memberInfo);
    public delegate void onSearchChannelsDelegate(List<ChannelInfo> channelInfos);
}
