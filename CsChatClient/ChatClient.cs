using System;
using System.Collections.Generic;
using ClrChatClient;
using CsChatClient.Messages;
using CsChatClient.Messages.Notification;
using CsChatClient.Models;
using Newtonsoft.Json;

// ReSharper disable InconsistentNaming

namespace CsChatClient
{
    #region 全局状态监听，建议程序启动时设置

    /// <summary>
    /// 连接状态监听
    /// </summary>
    public interface ConnectionStatusListener
    {
        void onConnectionStatusChanged(int status);
    }


    /// <summary>
    /// 消息监听
    /// </summary>
    public interface ReceiveMessageListener
    {
        void onReceiveMessages(List<MessageEx> messages, bool hasMore);
        void onRecallMessage(long messageUid);
        void onDeleteMessage(long messageUid);
    };


    /// <summary>
    /// 用户信息变更监听
    /// </summary>
    public interface UserInfoUpdateListener
    {
        void onUserInfoUpdated(List<UserInfo> userInfos);
    }

    /// <summary>
    /// 群组信息变更监听
    /// </summary>
    public interface GroupInfoUpdateListener
    {
        void onGroupInfoUpdated(List<GroupInfo> groupInfos);
    }

    /// <summary>
    /// 群组成员变更监听
    /// </summary>
    public interface GroupMemberUpdateListener
    {
        void onGroupMemberUpdated(string groupId);
    }

    /// <summary>
    /// 联系人状态监听
    /// </summary>
    public interface ContactUpdateListener
    {
        void onContactUpdated(List<string> friendUids);
    }

    /// <summary>
    /// 好友请求状态变更坚挺
    /// </summary>
    public interface FriendRequestUpdateListener
    {
        void onFriendRequestUpdated();
    }

    /// <summary>
    /// 用户设置监听
    /// </summary>
    public interface UserSettingUpdateListener
    {
        void onUserSettingUpdated();
    }

    /// <summary>
    /// 频道信息变更监听
    /// </summary>
    public interface ChannelInfoUpdateListener
    {
        void onChannelInfoUpdated(List<ChannelInfo> channelInfos);
    }


    /// <summary>
    /// 事件回调，一般都是一次性的。
    /// </summary>
    /// <summary>
    /// 通用的void的事件回调
    /// </summary>
    public interface GeneralVoidCallback
    {
        void onSuccess();
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 通用的string的事件回调
    /// </summary>
    public interface GeneralStringCallback
    {
        void onSuccess(string value);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 获取远程历史消息回调
    /// </summary>
    public interface GetRemoteMessageCallback
    {
        void onSuccess(List<MessageEx> messages);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 发送消息回调
    /// </summary>
    public interface WFSendMessageCallback
    {
        void onSuccess(long messageUid, long timestamp);

        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void onProgress(int uploaded, int total);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 搜索用户回调
    /// </summary>
    public interface SearchUserCallback
    {
        void onSuccess(List<UserInfo> messages);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 获取聊天室信息回调
    /// </summary>
    public interface GetChatroomInfoCallback
    {
        void onSuccess(ChatroomInfo chatroomInfo);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 获取聊天室成员信息回调
    /// </summary>
    public interface GetChatroomMemberInfoCallback
    {
        void onSuccess(ChatroomMemberInfo chatroomMemberInfo);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 获取频道信息回调
    /// </summary>
    public interface GetChannelInfoCallback
    {
        void onSuccess(ChannelInfo channelInfo);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 搜索频道回调
    /// </summary>
    public interface SearchChannelCallback
    {
        void onSuccess(List<ChannelInfo> channels);
        void onFailure(int errorCode);
    }

    /// <summary>
    /// 上传媒体文件回调
    /// </summary>
    public interface UploadMediaCallback
    {
        void onSuccess(string remoteUrl);

        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void onProgress(int uploaded, int total);
        void onFailure(int errorCode);
    }

    #endregion

    #region 枚举类型

    /// <summary>
    /// 会话类型
    /// </summary>
    public enum ConversationType
    {
        /// <summary>
        /// 单聊
        /// </summary>
        Single_Type,

        /// <summary>
        /// 群组
        /// </summary>
        Group_Type,

        /// <summary>
        /// 聊天室
        /// </summary>
        Chatroom_Type,

        /// <summary>
        /// 频道
        /// </summary>
        Channel_Type,
    }

    /// <summary>
    /// 搜索用户类型
    /// </summary>
    public enum SearchUserType
    {
        /// <summary>
        /// 模糊搜索diaplayName，精确匹配name和电话
        /// </summary>
        SearchUserType_General,

        /// <summary>
        /// 精确匹配name和电话
        /// </summary>
        SearchUserType_Name_Mobile,

        /// <summary>
        /// 精确匹配name
        /// </summary>
        SearchUserType_Name,

        /// <summary>
        /// 精确匹配电话
        /// </summary>
        SearchUserType_Mobile
    }

    /// <summary>
    /// 群組类型
    /// </summary>
    public enum GroupType
    {
        /// <summary>
        /// 微信风格群组
        /// </summary>
        GroupType_Normal,

        /// <summary>
        /// 自由风格
        /// </summary>
        GroupType_Free,

        /// <summary>
        /// 带有群管理的群，建议用这个
        /// </summary>
        GroupType_Restricted,
    }

    /// <summary>
    /// 群成員類型
    /// </summary>
    public enum GroupMemberType
    {
        Normal,
        Manager,
        Owner,
        Silent,
        Removed
    }


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
    }

    /// <summary>
    /// 修改个人信息的内容
    /// </summary>
    public enum ModifyMyInfoType
    {
        /// <summary>
        /// 修改显示名
        /// </summary>
        Modify_DisplayName = 0,

        /// <summary>
        /// 修改头像
        /// </summary>
        Modify_Portrait = 1,

        /// <summary>
        /// 修改性别
        /// </summary>
        Modify_Gender = 2,

        /// <summary>
        /// 修改手机号
        /// </summary>
        Modify_Mobile = 3,

        /// <summary>
        /// 修改邮箱
        /// </summary>
        Modify_Email = 4,

        /// <summary>
        /// 修改地址
        /// </summary>
        Modify_Address = 5,

        /// <summary>
        /// 修改公司信息
        /// </summary>
        Modify_Company = 6,

        /// <summary>
        /// 修改社交信息
        /// </summary>
        Modify_Social = 7,

        /// <summary>
        /// 修改扩展信息
        /// </summary>
        Modify_Extra = 8
    }

    public enum ModifyGroupInfoType
    {
        Modify_Group_Name = 0,
        Modify_Group_Portrait = 1,
        Modify_Group_Extra = 2,
        Modify_Group_Mute = 3,
        Modify_Group_JoinType = 4,
        Modify_Group_PrivateChat = 5,
        Modify_Group_Searchable = 6
    }


    public enum ModifyChannelInfoType
    {
        Modify_Channel_Name = 0,
        Modify_Channel_Portrait = 1,
        Modify_Channel_Desc = 2,
        Modify_Channel_Extra = 3,
        Modify_Channel_Secret = 4,
        Modify_Channel_Callback = 5
    }

    /// <summary>
    /// 媒体类型
    /// </summary>
    public enum MediaType
    {
        /// <summary>
        /// 一般
        /// </summary>
        Media_Type_GENERAL = 0,

        /// <summary>
        /// 图片
        /// </summary>
        Media_Type_IMAGE = 1,

        /// <summary>
        /// 语音
        /// </summary>
        Media_Type_VOICE = 2,

        /// <summary>
        /// 视频
        /// </summary>
        Media_Type_VIDEO = 3,

        /// <summary>
        /// 文件
        /// </summary>
        Media_Type_File = 4,

        /// <summary>
        /// 头像
        /// </summary>
        Media_Type_PORTRAIT = 5,

        /// <summary>
        /// 收藏
        /// </summary>
        Media_Type_FAVORITE = 6
    }

    /// <summary>
    /// 连接状态
    /// </summary>
    public enum ConnectionStatus
    {
        /// <summary>
        /// 密钥错误
        /// </summary>
        kConnectionStatusSecretKeyMismatch = -6,

        /// <summary>
        /// Token错误
        /// </summary>
        kConnectionStatusTokenIncorrect = -5,

        /// <summary>
        /// 服务器关闭
        /// </summary>
        kConnectionStatusServerDown = -4,

        /// <summary>
        /// 被拒绝
        /// </summary>
        kConnectionStatusRejected = -3,

        /// <summary>
        /// 退出登录
        /// </summary>
        kConnectionStatusLogout = -2,

        /// <summary>
        /// 未连接
        /// </summary>
        kConnectionStatusUnconnected = -1,

        /// <summary>
        /// 连接中
        /// </summary>
        kConnectionStatusConnecting = 0,

        /// <summary>
        /// 已连接
        /// </summary>
        kConnectionStatusConnected = 1,

        /// <summary>
        /// 获取离线消息中，可忽略
        /// </summary>
        kConnectionStatusReceiving = 2
    }

    /// <summary>
    /// 正在输入类型
    /// </summary>
    public enum TypingType
    {
        /// <summary>
        /// 正在输入文本
        /// </summary>
        Typing_TEXT = 0,

        /// <summary>
        /// 正在输入语音
        /// </summary>
        Typing_VOICE = 1,

        /// <summary>
        /// 正在拍摄
        /// </summary>
        Typing_CAMERA = 2,

        /// <summary>
        /// 正在选取位置
        /// </summary>
        Typing_LOCATION = 3,

        /// <summary>
        /// 正在选取文件
        /// </summary>
        Typing_FILE = 4
    }

    /// <summary>
    /// 消息方向
    /// </summary>
    public enum MessageDirection
    {
        /// <summary>
        /// 当前用户发送的消息
        /// </summary>
        Direction_Send = 0,

        /// <summary>
        /// 当前用户接收的消息
        /// </summary>
        Direction_Receive = 1
    }

    /// <summary>
    /// 说明：1000以下为系统保留类型，自定义消息请使用1000以上数值。
    /// 系统消息类型中100以下为常用基本类型消息。100-199位群组消息类型。400-499为VoIP消息类型.
    /// 基本消息类型
    /// </summary>
    public enum MessageContentType
    {
        /// <summary>
        /// 未知类型的消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_UNKNOWN = 0,

        /// <summary>
        /// 文本消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_TEXT = 1,

        /// <summary>
        /// 语音消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_SOUND = 2,

        /// <summary>
        /// 图片消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_IMAGE = 3,

        /// <summary>
        /// 位置消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_LOCATION = 4,

        /// <summary>
        /// 文件消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_FILE = 5,

        /// <summary>
        /// 视频消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_VIDEO = 6,

        /// <summary>
        /// 动态表情消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_STICKER = 7,

        /// <summary>
        /// 图文消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_IMAGETEXT = 8,

        /// <summary>
        /// 存储不计数文本消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_P_TEXT = 9,

        /// <summary>
        /// 撤回消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_RECALL = 80,

        /// <summary>
        /// 提醒消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_TIP = 90,

        /// <summary>
        /// 正在输入消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_TYPING = 91,

        //通知消息类型

        /// <summary>
        /// 创建群的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_CREATE_GROUP = 104,

        /// <summary>
        /// 加群的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_ADD_GROUP_MEMBER = 105,

        /// <summary>
        /// 踢出群成员的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_KICKOF_GROUP_MEMBER = 106,

        /// <summary>
        /// 退群的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_QUIT_GROUP = 107,

        /// <summary>
        /// 解散群的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_DISMISS_GROUP = 108,

        /// <summary>
        /// 转让群主的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_TRANSFER_GROUP_OWNER = 109,

        /// <summary>
        /// 修改群名称的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_CHANGE_GROUP_NAME = 110,

        /// <summary>
        /// 修改群昵称的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_MODIFY_GROUP_ALIAS = 111,

        /// <summary>
        /// 修改群头像的通知消息
        /// </summary>
        MESSAGE_CONTENT_TYPE_CHANGE_GROUP_PORTRAIT = 112,

        MESSAGE_CONTENT_TYPE_CHANGE_MUTE = 113,
        MESSAGE_CONTENT_TYPE_CHANGE_JOINTYPE = 114,
        MESSAGE_CONTENT_TYPE_CHANGE_PRIVATECHAT = 115,
        MESSAGE_CONTENT_TYPE_CHANGE_SEARCHABLE = 116,
        MESSAGE_CONTENT_TYPE_SET_MANAGER = 117,

        /// <summary>
        /// VoIP开始消息
        /// </summary>
        VOIP_CONTENT_TYPE_START = 400,
    }

    /// <summary>
    /// 消息存储类型
    /// </summary>
    public enum MessageContentPersistFlag
    {
        /// <summary>
        /// 本地不存储
        /// </summary>
        PersistFlag_NOT_PERSIST = 0,

        /// <summary>
        /// 本地存储
        /// </summary>
        PersistFlag_PERSIST = 1,

        /// <summary>
        ///  本地存储，并计入未读计数
        /// </summary>
        PersistFlag_PERSIST_AND_COUNT = 3,

        /// <summary>
        ///  透传消息，不多端同步，如果对端不在线，消息会丢弃
        /// </summary>
        PersistFlag_TRANSPARENT = 4,
    }

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
    }

    #endregion

    public class ChatClient
    {
        static public ChatClient Instance()
        {
            return INSTANCE;
        }

        #region 设置监听

        /// <summary>
        /// 设置连接状态监听，在connect之前调用
        /// </summary>
        /// <param name="listener">连接回调监听</param>
        public void setConnectionStatusListener(ConnectionStatusListener listener)
        {
            PROTO.setConnectStatusListener(listener.onConnectionStatusChanged);
        }

        /// <summary>
        /// 设置接受消息监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setReceiveMessageListener(ReceiveMessageListener listener)
        {
            PROTO.setMessageListener(new ReceiveMessageWrapper(listener).onReceive, listener.onRecallMessage, listener.onDeleteMessage);
        }


        /// <summary>
        /// 设置用戶信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setUserInfoUpdateListener(UserInfoUpdateListener listener)
        {
            PROTO.setUserInfoUpdateListener(new UserInfoUpdateWrapper(listener).onUserInfoUpdated);
        }

        /// <summary>
        /// 设置群組信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setGroupInfoUpdateListener(GroupInfoUpdateListener listener)
        {
            PROTO.setGroupInfoUpdateListener(new GroupInfoUpdateWrapper(listener).onGroupInfoUpdated);
        }

        /// <summary>
        /// 设置群組成員信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setGroupMemberUpdateListener(GroupMemberUpdateListener listener)
        {
            PROTO.setGroupMemberUpdateListener(listener.onGroupMemberUpdated);
        }

        /// <summary>
        /// 设置聯係人狀態變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setContactUpdateListener(ContactUpdateListener listener)
        {
            PROTO.setContactUpdateListener(new ContactUpdateWrapper(listener).onContactUpdated);
        }

        /// <summary>
        /// 设置好友請求變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setFriendRequestUpdateListener(FriendRequestUpdateListener listener)
        {
            PROTO.setFriendRequestUpdateListener(listener.onFriendRequestUpdated);
        }

        /// <summary>
        /// 设置設置监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setUserSettingUpdateListener(UserSettingUpdateListener listener)
        {
            PROTO.setUserSettingUpdateListener(listener.onUserSettingUpdated);
        }

        /// <summary>
        /// 设置頻道信息更新监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void setChannelInfoUpdateListener(ChannelInfoUpdateListener listener)
        {
            PROTO.setChannelInfoUpdateListener(new ChannelInfoUpdateWrapper(listener).onChannelInfoUpdated);
        }

        #endregion

        #region 客户端API

        /// <summary>
        /// 设置自定义消息元宵，在connect之前调用，实现方法请参考文本文件
        /// </summary>
        /// <param name="prototype">自定义消息原型</param>
        public void registerMessage(Type type)
        {
            ContentAttribute attribute = (ContentAttribute) Attribute.GetCustomAttribute(type, typeof(ContentAttribute));
            if (attribute != null)
            {
                MessageContentTypeDict[attribute.Type] = type;
                PROTO.registerMessageFlag(attribute.Type, (int) attribute.Flag);
            }
        }

        /// <summary>
        /// 获取当前设备的设备Id
        /// </summary>
        public string getClientId()
        {
            return PROTO.getClientId();
        }

        /// <summary>
        /// 连接IM服务。注意必须getClientId函数获取当前机器的id，然后使用clientId获取token，不然将会连接失败。程序結束前需要調用disconnect。
        /// </summary>
        /// <param name="userId">用户Id</param>
        /// <param name="token">用户令牌</param>
        public bool connect(string userId, string token)
        {
            registerMessage(typeof(TextMessageContent));
            registerMessage(typeof(CallStartMessageContent));
            registerMessage(typeof(FileMessageContent));
            registerMessage(typeof(ImageMessageContent));
            registerMessage(typeof(ImageTextMessageContent));
            registerMessage(typeof(LocationMessageContent));
            registerMessage(typeof(PTextMessageContent));
            registerMessage(typeof(SoundMessageContent));
            registerMessage(typeof(StickerMessageContent));
            registerMessage(typeof(TypingMessageContent));
            registerMessage(typeof(VideoMessageContent));

            registerMessage(typeof(AddGroupMemberNotificationContent));
            registerMessage(typeof(ChangeGroupNameNotificationContent));
            registerMessage(typeof(ChangeGroupPortraitNotificationContent));
            registerMessage(typeof(CreateGroupNotificationContent));
            registerMessage(typeof(DismissGroupNotificationContent));
            registerMessage(typeof(GroupJoinTypeNotificationContent));
            registerMessage(typeof(GroupMuteNotificationContent));
            registerMessage(typeof(GroupMuteNotificationContent));
            registerMessage(typeof(GroupPrivateChatNotificationContent));
            registerMessage(typeof(GroupSetManagerChatNotificationContent));
            registerMessage(typeof(KickoffGroupMemberNotificationContent));
            registerMessage(typeof(ModifyGroupAliasNotificationContent));
            registerMessage(typeof(QuitGroupNotificationContent));
            registerMessage(typeof(RecallMessageContent));
            registerMessage(typeof(TipNotificationContent));
            registerMessage(typeof(TransferGroupOwnerNotificationContent));
            
            return PROTO.connect(userId, token);
        }

        /// <summary>
        /// 斷開連接
        /// </summary>
        public void disconnect()
        {
            PROTO.disconnect();
        }

        /// <summary>
        /// 当前是否已经调用connect
        /// </summary>
        public bool isLogined()
        {
            return PROTO.isLogined();
        }

        /// <summary>
        /// 获取当前连接状态
        /// </summary>
        public ConnectionStatus getConnectionStatus()
        {
            return (ConnectionStatus) PROTO.getConnectionStatus();
        }

        /// <summary>
        /// 获取当前登录用户的用户Id
        /// </summary>
        public string getCurrentUserId()
        {
            return PROTO.getCurrentUserId();
        }

        /// <summary>
        /// 获取本地时间与服务器时间的差值，精确度不高。
        /// </summary>
        public long getServerDeltaTime()
        {
            return PROTO.getServerDeltaTime();
        }

        #endregion

        #region 会话API

        /// <summary>
        /// 获取会话信息
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <returns>会话信息</returns>
        public List<ConversationInfo> getConversationInfos(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            string infoStr = PROTO.getConversationInfos(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationInfo> cs = JsonConvert.DeserializeObject<List<ConversationInfo>>(infoStr, convert);
            return cs;
        }


        /// <summary>
        /// 获取会话信息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>会话信息</returns>
        public ConversationInfo getConversationInfo(Conversation conversation)
        {
            string info = PROTO.getConversationInfo((int) conversation.Type, conversation.Target, conversation.Line);

            WfcJsonConverter convert = new WfcJsonConverter();
            ConversationInfo ci = JsonConvert.DeserializeObject<ConversationInfo>(info, convert);
            return ci;
        }

        /// <summary>
        /// 搜索会话
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <returns>会话搜索结果信息</returns>
        public List<ConversationSearchInfo> searchConversation(string keyword, List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            string infos = PROTO.searchConversation(keyword, types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationSearchInfo> cs = JsonConvert.DeserializeObject<List<ConversationSearchInfo>>(infos, convert);
            return cs;
        }

        /// <summary>
        /// 删除会话
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="clearMessage">是否删除会话中的消息</param>
        public void removeConversation(Conversation conversation, bool clearMessage)
        {
            PROTO.removeConversation((int) conversation.Type, conversation.Target, conversation.Line, clearMessage);
        }

        /// <summary>
        /// 设置或取消会话置顶
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="top">是否置顶</param>
        /// <param name="callback">结果回调</param>
        public void setConversationTop(Conversation conversation, bool top, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setConversationTop((int) conversation.Type, conversation.Target, conversation.Line, top, () => { succDele(); }, (int errorCode) => { errDele(errorCode); });
        }

        /// <summary>
        /// 设置会话免打扰
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="silent">是否免打扰</param>
        /// <param name="callback">结果回调</param>
        public void setConversationSilent(Conversation conversation, bool silent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setConversationSilent((int) conversation.Type, conversation.Target, conversation.Line, silent, () => { succDele(); }, (int errorCode) => { errDele(errorCode); });
        }

        /// <summary>
        /// 设置会话草稿
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="draft">草稿</param>
        public void setConversationDraft(Conversation conversation, string draft)
        {
            PROTO.setConversationDraft((int) conversation.Type, conversation.Target, conversation.Line, draft);
        }

        /// <summary>
        /// 获取指定类型会话的未读数
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <returns>未读数</returns>
        public UnreadCount getUnreadCount(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            string unreadStr = PROTO.getUnreadCount(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /// <summary>
        /// 获取某个会话的未读数
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>未读数</returns>
        public UnreadCount getUnreadCount(Conversation conversation)
        {
            string unreadStr = PROTO.getUnreadCount((int) conversation.Type, conversation.Target, conversation.Line);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /// <summary>
        /// 清空会话未读数
        /// </summary>
        /// <param name="conversation">会话</param>
        public void clearUnreadStatus(Conversation conversation)
        {
            PROTO.clearUnreadStatus((int) conversation.Type, conversation.Target, conversation.Line);
        }

        /// <summary>
        /// 清空会话类型的未读数
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        public void clearUnreadStatus(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            PROTO.clearUnreadStatus(types, lines);
        }

        /// <summary>
        /// 清空所有会话的未读数
        /// </summary>
        public void clearAllUnreadStatus()
        {
            PROTO.clearAllUnreadStatus();
        }

        #endregion

        #region 消息API

        /// <summary>
        /// 设置媒体消息已播放
        /// </summary>
        /// <param name="messageId">消息ID</param>
        public void setMediaMessagePlayed(long messageId)
        {
            PROTO.setMediaMessagePlayed((int) messageId);
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="contentTypes">消息类型</param>
        /// <param name="fromIndex">起始index</param>
        /// <param name="count">总数</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> getMessages(Conversation conversation, List<int> contentTypes, long fromIndex, int count, string user)
        {
            string messagesStr = PROTO.getMessages((int) conversation.Type, conversation.Target, conversation.Line, contentTypes, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /// <summary>
        /// 获取某类会话信息
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <param name="contentTypes">消息类型</param>
        /// <param name="fromIndex">起始index</param>
        /// <param name="count">总数</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> getMessages(List<ConversationType> conversationTypes, List<int> lines, List<int> contentTypes, long fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            string messagesStr = PROTO.getMessages(types, lines, contentTypes, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /// <summary>
        /// 获取某类会话信息
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <param name="messageStatus">消息状态</param>
        /// <param name="fromIndex">起始index</param>
        /// <param name="count">总数</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> getMessages(List<ConversationType> conversationTypes, List<int> lines, MessageStatus messageStatus, long fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int) ct);
            }

            string messagesStr = PROTO.getMessages(types, lines, (int) messageStatus, fromIndex, count, user);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /// <summary>
        /// 获取服务器消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="beforeMessageUid">起始index</param>
        /// <param name="count">总数</param>
        /// <param name="callback">结果回调</param>
        public void getRemoteMessages(Conversation conversation, long beforeMessageUid, int count, onGetRemoteMessageDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getRemoteMessages((int) conversation.Type, conversation.Target, conversation.Line, beforeMessageUid, count, (string messages) =>
            {
                WfcJsonConverter convert = new WfcJsonConverter();
                List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messages, convert);
                succDele(ms);
            }, (int errorCode) => { errDele(errorCode); });
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <returns>消息实体</returns>
        public MessageEx getMessage(long messageId)
        {
            string messageStr = PROTO.getMessage((int) messageId);

            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="messageUid">消息UID</param>
        /// <returns>消息实体</returns>
        public MessageEx getMessageByUid(long messageUid)
        {
            string messageStr = PROTO.getMessageByUid(messageUid);

            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 搜索消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="keyword">关键词</param>
        /// <param name="count">数量</param>
        /// <returns>命中的消息</returns>
        public List<MessageEx> searchMessage(Conversation conversation, string keyword, int count)
        {
            string messagesStr = PROTO.searchMessage((int) conversation.Type, conversation.Target, conversation.Line, keyword, count);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messagesStr, convert);
            return ms;
        }

        /// <summary>
        /// 发送消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="content">消息内容</param>
        /// <param name="toUsers">在会话中只发给该用户，如果为空则发到会话中</param>
        /// <param name="expireDuration">消息的有效期，0不限期，单位秒</param>
        /// <param name="callback">发送结果回调</param>
        /// <returns>消息实体</returns>
        public MessageEx sendMessage(Conversation conversation, MessageContent content, List<string> toUsers, int expireDuration, onBigIntBigIntCallbackDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = PROTO.sendMessage((int) conversation.Type, conversation.Target, conversation.Line, contentStr, toUsers, expireDuration, succDele, progressDele, errDele);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 撤回消息
        /// </summary>
        /// <param name="messageUid">待撤回的消息Uid</param>
        /// <param name="callback">结果的回调</param>
        public void recallMessage(long messageUid, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.recallMessage(messageUid, succDele, errDele);
        }

        /// <summary>
        /// 上传媒体(图片、语音、文件等)
        /// </summary>
        /// <param name="fileName">文件名，可为空</param>
        /// <param name="mediaData">媒体信息</param>
        /// <param name="mediaType">媒体类型</param>
        /// <param name="callback">回调</param>
        public void uploadMedia(string fileName, string mediaData, MediaType mediaType, onUploadedMediaDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            PROTO.uploadMedia(fileName, mediaData, (int) mediaType, (string remoteUrl) => { succDele(remoteUrl); }, progressDele, errDele);
        }

        /// <summary>
        /// 删除消息
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <returns>是否删除成功</returns>
        public bool deleteMessage(long messageId)
        {
            return PROTO.deleteMessage((int) messageId);
        }

        /// <summary>
        /// 删除会话中的消息
        /// </summary>
        /// <param name="conversation">会话</param>
        public void clearMessages(Conversation conversation)
        {
            PROTO.clearMessages((int) conversation.Type, conversation.Target, conversation.Line);
        }

        /// <summary>
        /// 删除会话中的before之前的旧消息。
        /// </summary>
        /// <param name="conversation">会话，如果conversation为nil，则清除所有会话的消息。</param>
        /// <param name="before">时间点，单位是毫秒</param>
        public void clearMessages(Conversation conversation, long before)
        {
            PROTO.clearMessages((int) conversation.Type, conversation.Target, conversation.Line, before);
        }

        /// <summary>
        /// 插入消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="content">消息内容</param>
        /// <param name="status">消息状态，注意消息状态会影响消息方向</param>
        /// <param name="serverTime">时间，0为当前时间</param>
        /// <returns>消息实体</returns>
        public MessageEx insertMessage(Conversation conversation, string sender, MessageContent content, MessageStatus status, bool notify, long serverTime)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = PROTO.insert((int) conversation.Type, conversation.Target, conversation.Line, sender, contentStr, (int) status, notify, serverTime);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 更新消息内容
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <param name="content">消息内容</param>
        public void updateMessage(long messageId, MessageContent content)
        {
            var contentStr = JsonTools.Stringfy(content);
            PROTO.updateMessage((int) messageId, contentStr);
        }

        #endregion

        #region 用户API

        /// <summary>
        /// 获取用户信息
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。</param>
        /// <returns>本地的用户信息，可能为空</returns>
        public UserInfo getUserInfo(string userId, bool refresh)
        {
            string userStr = PROTO.getUserInfo(userId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            UserInfo ui = JsonConvert.DeserializeObject<UserInfo>(userStr, convert);
            return ui;
        }

        /// <summary>
        /// 获取用户信息
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="groupId">群组ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。</param>
        /// <returns>本地的用户信息，可能为空</returns>
        public UserInfo getUserInfo(string userId, string groupId, bool refresh)
        {
            string userStr = PROTO.getUserInfo(userId, groupId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            UserInfo ui = JsonConvert.DeserializeObject<UserInfo>(userStr, convert);
            return ui;
        }

        /// <summary>
        /// 批量获取用户信息
        /// </summary>
        /// <param name="userIds">用户ID列表</param>
        /// <param name="groupId">群组ID</param>
        /// <returns>本地的用户信息列表。本地不存在的用户会返回只有id的用户信息，同时会拉取。</returns>
        public List<UserInfo> getUserInfos(List<string> userIds, string groupId)
        {
            string usersStr = PROTO.getUserInfos(userIds, groupId);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
            return us;
        }

        /// <summary>
        /// 搜索用户
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <param name="searchType">搜索类型</param>
        /// <param name="page">page</param>
        /// <param name="callback">回调</param>
        public void searchUser(string keyword, SearchUserType searchType, int page, onSearchUsersDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.searchUser(keyword, (int) searchType, page, (string usersStr) =>
            {
                WfcJsonConverter convert = new WfcJsonConverter();
                List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
                succDele(us);
            }, errDele);
        }

        #endregion

        #region 好友API

        /// <summary>
        /// 查询用户和当前用户是否是好友关系
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns>是否是好友</returns>
        public bool isMyFriend(string userId)
        {
            return PROTO.isMyFriend(userId);
        }

        /// <summary>
        /// 获取当前用户的好友列表
        /// </summary>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>好友列表的用户ID</returns>
        public List<string> getMyFriendList(bool refresh)
        {
            string friendsStr = PROTO.getMyFriendList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }


        /// <summary>
        /// 搜索好友
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <returns>好友用户信息</returns>
        public List<UserInfo> searchFriends(string keyword)
        {
            string usersStr = PROTO.searchFriends(keyword);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
            return us;
        }

        /// <summary>
        /// 获取收到的好友请求
        /// </summary>
        /// <returns>好友请求</returns>
        public List<FriendRequest> getIncommingFriendRequest()
        {
            string usersStr = PROTO.getIncommingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /// <summary>
        /// 获取发出的好友请求
        /// </summary>
        /// <returns>好友请求</returns>
        public List<FriendRequest> getOutgoingFriendRequest()
        {
            string usersStr = PROTO.getOutgoingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /// <summary>
        /// 从服务器更新好友请求
        /// </summary>
        public void loadFriendRequestFromRemote()
        {
            PROTO.loadFriendRequestFromRemote();
        }

        /// <summary>
        /// 获取未读的好友请求数
        /// </summary>
        /// <returns>未读的好友请求数</returns>
        public int getUnreadFriendRequestStatus()
        {
            return PROTO.getUnreadFriendRequestStatus();
        }

        /// <summary>
        /// 清除好友请求的未读数
        /// </summary>
        public void clearUnreadFriendRequestStatus()
        {
            PROTO.clearUnreadFriendRequestStatus();
        }

        /// <summary>
        /// 删除好友
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="callback">回调</param>
        public void deleteFriend(string userId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.deleteFriend(userId, succDele, errDele);
        }

        /// <summary>
        /// 发送好友请求
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="reason">请求说明</param>
        /// <param name="callback">回调</param>
        public void sendFriendRequest(string userId, string reason, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.sendFriendRequest(userId, reason, succDele, errDele);
        }

        /// <summary>
        /// 处理好友请求
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="accpet">是否接受</param>
        /// <param name="friendExtra">extra</param>
        /// <param name="callback">回调</param>
        public void handleFriendRequest(string userId, bool accpet, string friendExtra, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.handleFriendRequest(userId, accpet, friendExtra, succDele, errDele);
        }

        /// <summary>
        /// 获取用户的别名
        /// </summary>
        /// <param name="userId">用户ID</param>
        public string getFriendAlias(string userId)
        {
            return PROTO.getFriendAlias(userId);
        }

        /// <summary>
        /// 设置用户的别名
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="alias">别名</param>
        /// <param name="callback">回调</param>
        public void setFriendAlias(string userId, string alias, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setFriendAlias(userId, alias, succDele, errDele);
        }

        /// <summary>
        /// 查询用户是否被加入黑名单
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns>是否被加入黑名单</returns>
        public bool isBlackListed(string userId)
        {
            return PROTO.isBlackListed(userId);
        }

        /// <summary>
        /// 获取当前用户的黑名单列表
        /// </summary>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>黑名单列表的用户ID</returns>
        public List<string> getBlackList(bool refresh)
        {
            string friendsStr = PROTO.getBlackList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }

        /// <summary>
        /// 设置黑名单
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="isBlackListed">YES</param>
        /// <param name="callback">回调</param>
        public void setBlackList(string userId, bool isBlackListed, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setBlackList(userId, isBlackListed, succDele, errDele);
        }

        #endregion

        #region 群组API

        /// <summary>
        /// 搜索群组
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <returns>群组搜索结果</returns>
        public List<GroupSearchInfo> searchGroups(string keyword)
        {
            string usersStr = PROTO.searchGroups(keyword);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<GroupSearchInfo> gs = JsonConvert.DeserializeObject<List<GroupSearchInfo>>(usersStr, convert);
            return gs;
        }

        /// <summary>
        /// 获取群成员信息
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="forceUpdate">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>群成员信息</returns>
        public List<GroupMember> getGroupMembers(string groupId, bool forceUpdate)
        {
            string membersStr = PROTO.getGroupMembers(groupId, forceUpdate);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<GroupMember> us = JsonConvert.DeserializeObject<List<GroupMember>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 获取群信息
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>群信息</returns>
        public GroupInfo getGroupInfo(string groupId, bool refresh)
        {
            string gStr = PROTO.getGroupInfo(groupId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            GroupInfo us = JsonConvert.DeserializeObject<GroupInfo>(gStr, convert);
            return us;
        }

        /// <summary>
        /// 获取群成员信息
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="memberId">群成员ID</param>
        /// <returns>群成员信息</returns>
        public GroupMember getGroupMember(string groupId, string memberId)
        {
            string memberStr = PROTO.getGroupMember(groupId, memberId);
            WfcJsonConverter convert = new WfcJsonConverter();
            GroupMember us = JsonConvert.DeserializeObject<GroupMember>(memberStr, convert);
            return us;
        }

        /// <summary>
        /// 创建群
        /// </summary>
        /// <param name="groupId">群ID,傳空時自動生成群組id，建議爲空</param>
        /// <param name="groupName">群名称</param>
        /// <param name="groupPortrait">群头像</param>
        /// <param name="groupMembers">群成员</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void createGroup(string groupId, string groupName, string groupPortrait, GroupType type, List<string> groupMembers, List<int> notifyLines, MessageContent notifyContent, onCreateGroupDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.createGroup(groupId, groupName, groupPortrait, (int) type, groupMembers, notifyLines, contentStr, (string gid) => { succDele(gid); }, errDele);
        }

        /// <summary>
        /// 添加群成员
        /// </summary>
        /// <param name="members">成员的用户ID列表</param>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void addMembers(List<string> members, string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.addMembers(members, groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 踢出群成员
        /// </summary>
        /// <param name="members">成员的用户ID列表</param>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void kickoffMembers(List<string> members, string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.kickoffMembers(members, groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 退群
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void quitGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.quitGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 解散群
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void dismissGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.dismissGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 修改群信息
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="type">要修改的群属性</param>
        /// <param name="newValue">要修改的群属性值</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void modifyGroupInfo(string groupId, ModifyGroupInfoType type, string newValue, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.modifyGroupInfo(groupId, (int) type, newValue, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 修改群昵称
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="newAlias">昵称</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void modifyGroupAlias(string groupId, string newAlias, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.modifyGroupAlias(groupId, newAlias, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 转移群主
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="newOwner">群主的用户ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void transferGroup(string groupId, string newOwner, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.transferGroup(groupId, newOwner, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 设置群管理
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="isSet">设置或取消</param>
        /// <param name="memberId">成员ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="callback">回调</param>
        public void setGroupManager(string groupId, bool isSet, List<string> memberIds, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            PROTO.setGroupManager(groupId, isSet, memberIds, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 获取当前用户收藏的群组
        /// </summary>
        /// <returns>当前用户收藏的群组ID</returns>
        public List<string> getFavGroups()
        {
            string membersStr = PROTO.getFavGroups();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 是否是当前用户收藏的群组
        /// </summary>
        /// <returns>是否是当前用户收藏的群组</returns>
        public bool isFavGroup(string groupId)
        {
            return PROTO.isFavGroup(groupId);
        }

        /// <summary>
        /// 设置群组收藏状态
        /// </summary>
        /// <param name="groupId">群组ID</param>
        /// <param name="fav">是否收藏</param>
        /// <param name="callback">回调</param>
        public void setFavGroup(string groupId, bool fav, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setFavGroup(groupId, fav, succDele, errDele);
        }

        #endregion

        #region 个人设置API

        /// <summary>
        /// 获取个人设置
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <param name="key">设置项的key</param>
        /// <returns>设置值</returns>
        public string getUserSetting(UserSettingScope scope, string key)
        {
            return PROTO.getUserSetting((int) scope, key);
        }

        /// <summary>
        /// 获取个人一类设置
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <returns>scope对应的所有设置值</returns>
        public Dictionary<string, string> getUserSettings(UserSettingScope scope)
        {
            return null;
        }

        /// <summary>
        /// 设置个人设置项
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <param name="key">设置项的key</param>
        /// <param name="value">值</param>
        /// <param name="callback">成功的回调</param>
        public void setUserSetting(UserSettingScope scope, string key, string value, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setUserSetting((int) scope, key, value, succDele, errDele);
        }

        /// <summary>
        /// 修改个人信息
        /// </summary>
        /// <param name="values">信息</param>
        /// <param name="callback">成功的回调</param>
        public void modifyMyInfo(Dictionary<int, string> values, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.modifyMyInfo(values, succDele, errDele);
        }

        /// <summary>
        /// 是否是全局禁止通知
        /// </summary>
        public bool isGlobalSlient()
        {
            return PROTO.isGlobalSlient();
        }

        /// <summary>
        /// 设置全局禁止通知
        /// </summary>
        /// <param name="slient">是否禁止通知</param>
        /// <param name="callback">回调</param>
        public void setGlobalSlient(bool slient, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setGlobalSlient(slient, succDele, errDele);
        }

        /// <summary>
        /// 通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
        /// </summary>
        public bool isHiddenNotificationDetail()
        {
            return PROTO.isHiddenNotificationDetail();
        }

        /// <summary>
        /// 设置通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
        /// </summary>
        /// <param name="hidden">是否隐藏详情</param>
        /// <param name="callback">回调</param>
        public void setHiddenNotificationDetail(bool hidden, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setHiddenNotificationDetail(hidden, succDele, errDele);
        }

        /// <summary>
        /// 群聊中是否显示群成员名称
        /// </summary>
        /// <param name="hidden">是否显示</param>
        /// <param name="groupId">群组ID</param>
        /// <param name="callback">回调</param>
        public void setHiddenGroupMemberName(bool hidden, string groupId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.setHiddenGroupMemberName(hidden, groupId, succDele, errDele);
        }

        #endregion

        #region 聊天室API

        /// <summary>
        /// 加入聊天室
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="callback">回调</param>
        public void joinChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.joinChatroom(chatroomId, succDele, errDele);
        }

        /// <summary>
        /// 退出聊天室
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="callback">回调</param>
        public void quitChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.quitChatroom(chatroomId, succDele, errDele);
        }

        /// <summary>
        /// 获取聊天室信息
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="updateDt">上次聊天室获取时间戳，可以为0</param>
        /// <param name="callback">回调</param>
        public void getChatroomInfo(string chatroomId, long updateDt, onGetChatroomInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getChatroomInfo(chatroomId, updateDt, (string str) =>
            {
                ChatroomInfo chatroomInfo = JsonTools.Jsonfy<ChatroomInfo>(str);
                succDele(chatroomInfo);
            }, errDele);
        }

        /// <summary>
        /// 获取聊天室成员信息
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="maxCount">最大成员数量，建议不超过100</param>
        /// <param name="callback">回调</param>
        public void getChatroomMemberInfo(string chatroomId, int maxCount, onGetChatroomMemberInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.getChatroomMemberInfo(chatroomId, maxCount, (string str) =>
            {
                ChatroomMemberInfo memberInfo = JsonTools.Jsonfy<ChatroomMemberInfo>(str);
            }, errDele);
        }

        #endregion

        #region 频道API

        /// <summary>
        /// 创建频道
        /// </summary>
        /// <param name="channelName">频道名称</param>
        /// <param name="channelPortrait">频道头像</param>
        /// <param name="status">频道状态，这里使用0</param>
        /// <param name="desc">频道描述</param>
        /// <param name="extra">频道extra</param>
        /// <param name="callback">回调</param>
        public void createChannel(string channelName, string channelPortrait, int status, string desc, string extra, onGeneralStringSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.createChannel(channelName, channelPortrait, status, desc, extra, succDele, errDele);
        }

        /// <summary>
        /// 获取频道信息
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>群信息</returns>
        public ChannelInfo getChannelInfo(string channelId, bool refresh)
        {
            string str = PROTO.getChannelInfo(channelId, refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            ChannelInfo us = JsonConvert.DeserializeObject<ChannelInfo>(str, convert);
            return us;
        }

        /// <summary>
        /// 修改频道信息
        /// </summary>
        /// <param name="channelId">群ID</param>
        /// <param name="type">要修改的群属性</param>
        /// <param name="newValue">要修改的群属性值</param>
        /// <param name="callback">回调</param>
        public void modifyChannelInfo(string channelId, ModifyChannelInfoType type, string newValue, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.modifyChannelInfo(channelId, (int) type, newValue, succDele, errDele);
        }

        /// <summary>
        /// 搜索频道
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <param name="callback">回调</param>
        public void searchChannel(string keyword, onSearchChannelsDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.searchChannel(keyword, (string str) =>
            {
                List<ChannelInfo> channels = JsonTools.Jsonfy<List<ChannelInfo>>(str);
                succDele(channels);
            }, errDele);
        }

        /// <summary>
        /// 是否收听频道
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <returns>YES，收听；NO，未收听</returns>
        public bool isListenedChannel(string channelId)
        {
            return PROTO.isListenedChannel(channelId);
        }

        /// <summary>
        /// 收听或者取消收听频道
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="listen">是否收听</param>
        /// <param name="callback">回调</param>
        public void listenChannel(string channelId, bool listen, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.listenChannel(channelId, listen, succDele, errDele);
        }

        /// <summary>
        /// 获取当前用户创建的频道
        /// </summary>
        /// <returns>当前用户创建的频道ID</returns>
        public List<string> getMyChannels()
        {
            string membersStr = PROTO.getMyChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 获取当前用户收听的频道
        /// </summary>
        /// <returns>当前用户收听的频道ID</returns>
        public List<string> getListenedChannels()
        {
            string membersStr = PROTO.getListenedChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 销毁频道
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="callback">回调</param>
        public void destoryChannel(string channelId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            PROTO.destoryChannel(channelId, succDele, errDele);
        }

        #endregion

        class ReceiveMessageWrapper
        {
            public ReceiveMessageWrapper(ReceiveMessageListener listener)
            {
                m_listener = listener;
            }

            private ReceiveMessageListener m_listener;

            public void onReceive(string messages, bool hasMore)
            {
                List<MessageEx> ms = JsonTools.Jsonfy<List<MessageEx>>(messages);
                m_listener.onReceiveMessages(ms, hasMore);
            }
        }

        class UserInfoUpdateWrapper
        {
            public UserInfoUpdateWrapper(UserInfoUpdateListener listener)
            {
                m_listener = listener;
            }

            private UserInfoUpdateListener m_listener;

            public void onUserInfoUpdated(string users)
            {
                List<UserInfo> userInfos = JsonTools.Jsonfy<List<UserInfo>>(users);
                m_listener.onUserInfoUpdated(userInfos);
            }
        }

        class GroupInfoUpdateWrapper
        {
            public GroupInfoUpdateWrapper(GroupInfoUpdateListener listener)
            {
                m_listener = listener;
            }

            private GroupInfoUpdateListener m_listener;

            public void onGroupInfoUpdated(string groups)
            {
                List<GroupInfo> groupInfos = JsonTools.Jsonfy<List<GroupInfo>>(groups);
                m_listener.onGroupInfoUpdated(groupInfos);
            }
        }

        class ContactUpdateWrapper
        {
            public ContactUpdateWrapper(ContactUpdateListener listener)
            {
                m_listener = listener;
            }

            private ContactUpdateListener m_listener;

            public void onContactUpdated(string groups)
            {
                List<string> friends = JsonTools.Jsonfy<List<string>>(groups);
                m_listener.onContactUpdated(friends);
            }
        }

        class ChannelInfoUpdateWrapper
        {
            public ChannelInfoUpdateWrapper(ChannelInfoUpdateListener listener)
            {
                m_listener = listener;
            }

            private ChannelInfoUpdateListener m_listener;

            public void onChannelInfoUpdated(string groups)
            {
                List<ChannelInfo> groupInfos = JsonTools.Jsonfy<List<ChannelInfo>>(groups);
                m_listener.onChannelInfoUpdated(groupInfos);
            }
        }


        public MessageContent getContent(MessagePayload payload)
        {
            MessageContent content;
            if (MessageContentTypeDict.ContainsKey(payload.ContentType))
            {
                Type type = MessageContentTypeDict[payload.ContentType];
                content = (MessageContent) Activator.CreateInstance(type);
            }
            else
            {
                content = new UnknownMessageContent();
            }

            try
            {
                content.Decode(payload);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
            
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