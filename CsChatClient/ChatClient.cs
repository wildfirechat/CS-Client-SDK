using System;
using System.Collections.Generic;
using ClrChatClient;
using CsChatClient.Messages;
using CsChatClient.Messages.Notification;
using CsChatClient.Models;
using Newtonsoft.Json;

namespace CsChatClient
{
    #region 全局状态监听，建议程序启动时设置

    /// <summary>
    /// 连接状态监听
    /// </summary>
    public interface IConnectionStatusListener
    {
        void OnConnectionStatusChanged(int status);
    }


    /// <summary>
    /// 消息监听
    /// </summary>
    public interface IReceiveMessageListener
    {
        void OnReceiveMessages(List<MessageEx> messages, bool hasMore);
        void OnRecallMessage(long messageUid);
        void OnDeleteMessage(long messageUid);
        void OnMessageDeliveried(Dictionary<string, long> deliveryInfos);
        void OnMessageReaded(List<ReadEntry> readedInfos);

    };


    /// <summary>
    /// 用户信息变更监听
    /// </summary>
    public interface IUserInfoUpdateListener
    {
        void OnUserInfoUpdated(List<UserInfo> userInfos);
    }

    /// <summary>
    /// 群组信息变更监听
    /// </summary>
    public interface IGroupInfoUpdateListener
    {
        void OnGroupInfoUpdated(List<GroupInfo> groupInfos);
    }

    /// <summary>
    /// 群组成员变更监听
    /// </summary>
    public interface IGroupMemberUpdateListener
    {
        void OnGroupMemberUpdated(string groupId);
    }

    /// <summary>
    /// 联系人状态监听
    /// </summary>
    public interface IContactUpdateListener
    {
        void OnContactUpdated(List<string> friendUids);
    }

    /// <summary>
    /// 好友请求状态变更坚挺
    /// </summary>
    public interface IFriendRequestUpdateListener
    {
        void OnFriendRequestUpdated(List<string> friendUids);
    }

    /// <summary>
    /// 用户设置监听
    /// </summary>
    public interface IUserSettingUpdateListener
    {
        void OnUserSettingUpdated();
    }

    /// <summary>
    /// 频道信息变更监听
    /// </summary>
    public interface IChannelInfoUpdateListener
    {
        void OnChannelInfoUpdated(List<ChannelInfo> channelInfos);
    }


    /// <summary>
    /// 事件回调，一般都是一次性的。
    /// </summary>
    /// <summary>
    /// 通用的void的事件回调
    /// </summary>
    public interface IGeneralVoidCallback
    {
        void OnSuccess();
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 通用的string的事件回调
    /// </summary>
    public interface IGeneralStringCallback
    {
        void OnSuccess(string value);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 获取远程历史消息回调
    /// </summary>
    public interface IGetRemoteMessageCallback
    {
        void OnSuccess(List<MessageEx> messages);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 发送消息回调
    /// </summary>
    public interface IWFSendMessageCallback
    {
        void OnSuccess(long messageUid, long timestamp);

        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void OnProgress(int uploaded, int total);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 搜索用户回调
    /// </summary>
    public interface ISearchUserCallback
    {
        void OnSuccess(List<UserInfo> messages);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 获取聊天室信息回调
    /// </summary>
    public interface IGetChatroomInfoCallback
    {
        void OnSuccess(ChatroomInfo chatroomInfo);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 获取聊天室成员信息回调
    /// </summary>
    public interface IGetChatroomMemberInfoCallback
    {
        void OnSuccess(ChatroomMemberInfo chatroomMemberInfo);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 获取频道信息回调
    /// </summary>
    public interface IGetChannelInfoCallback
    {
        void OnSuccess(ChannelInfo channelInfo);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 搜索频道回调
    /// </summary>
    public interface ISearchChannelCallback
    {
        void OnSuccess(List<ChannelInfo> channels);
        void OnFailure(int errorCode);
    }

    /// <summary>
    /// 上传媒体文件回调
    /// </summary>
    public interface IUploadMediaCallback
    {
        void OnSuccess(string remoteUrl);

        // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
        void OnProgress(int uploaded, int total);
        void OnFailure(int errorCode);
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
        SingleType,

        /// <summary>
        /// 群组
        /// </summary>
        GroupType,

        /// <summary>
        /// 聊天室
        /// </summary>
        ChatroomType,

        /// <summary>
        /// 频道
        /// </summary>
        ChannelType,
    }

    /// <summary>
    /// 搜索用户类型
    /// </summary>
    public enum SearchUserType
    {
        /// <summary>
        /// 模糊搜索diaplayName，精确匹配name和电话
        /// </summary>
        SearchUserTypeGeneral,

        /// <summary>
        /// 精确匹配name和电话
        /// </summary>
        SearchUserTypeNameMobile,

        /// <summary>
        /// 精确匹配name
        /// </summary>
        SearchUserTypeName,

        /// <summary>
        /// 精确匹配电话
        /// </summary>
        SearchUserTypeMobile
    }

    /// <summary>
    /// 群組类型
    /// </summary>
    public enum GroupType
    {
        /// <summary>
        /// 微信风格群组
        /// </summary>
        GroupTypeNormal,

        /// <summary>
        /// 自由风格
        /// </summary>
        GroupTypeFree,

        /// <summary>
        /// 带有群管理的群，建议用这个
        /// </summary>
        GroupTypeRestricted,
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
        KUserSettingConversationSilent = 1,
        KUserSettingGlobalSilent = 2,
        KUserSettingConversationTop = 3,
        KUserSettingHiddenNotificationDetail = 4,
        KUserSettinGroupHideNickname = 5,
        KUserSettingFavouriteGroup = 6,
        KUserSettingConversationSync = 7,
        KUserSettingMyChannels = 8,
        KUserSettingListenedChannels = 9,

        KUserSettingCustomBegin = 1000
    }

    /// <summary>
    /// 修改个人信息的内容
    /// </summary>
    public enum ModifyMyInfoType
    {
        /// <summary>
        /// 修改显示名
        /// </summary>
        ModifyDisplayName = 0,

        /// <summary>
        /// 修改头像
        /// </summary>
        ModifyPortrait = 1,

        /// <summary>
        /// 修改性别
        /// </summary>
        ModifyGender = 2,

        /// <summary>
        /// 修改手机号
        /// </summary>
        ModifyMobile = 3,

        /// <summary>
        /// 修改邮箱
        /// </summary>
        ModifyEmail = 4,

        /// <summary>
        /// 修改地址
        /// </summary>
        ModifyAddress = 5,

        /// <summary>
        /// 修改公司信息
        /// </summary>
        ModifyCompany = 6,

        /// <summary>
        /// 修改社交信息
        /// </summary>
        ModifySocial = 7,

        /// <summary>
        /// 修改扩展信息
        /// </summary>
        ModifyExtra = 8
    }

    public enum ModifyGroupInfoType
    {
        ModifyGroupName = 0,
        ModifyGroupPortrait = 1,
        ModifyGroupExtra = 2,
        ModifyGroupMute = 3,
        ModifyGroupJoinType = 4,
        ModifyGroupPrivateChat = 5,
        ModifyGroupSearchable = 6
    }


    public enum ModifyChannelInfoType
    {
        ModifyChannelName = 0,
        ModifyChannelPortrait = 1,
        ModifyChannelDesc = 2,
        ModifyChannelExtra = 3,
        ModifyChannelSecret = 4,
        ModifyChannelCallback = 5
    }

    /// <summary>
    /// 媒体类型
    /// </summary>
    public enum MediaType
    {
        /// <summary>
        /// 一般
        /// </summary>
        MediaTypeGeneral = 0,

        /// <summary>
        /// 图片
        /// </summary>
        MediaTypeImage = 1,

        /// <summary>
        /// 语音
        /// </summary>
        MediaTypeVoice = 2,

        /// <summary>
        /// 视频
        /// </summary>
        MediaTypeVideo = 3,

        /// <summary>
        /// 文件
        /// </summary>
        MediaTypeFile = 4,

        /// <summary>
        /// 头像
        /// </summary>
        MediaTypePortrait = 5,

        /// <summary>
        /// 收藏
        /// </summary>
        MediaTypeFavorite = 6
    }

    /// <summary>
    /// 连接状态
    /// </summary>
    public enum ConnectionStatus
    {
        /// <summary>
        /// 密钥错误
        /// </summary>
        KConnectionStatusSecretKeyMismatch = -6,

        /// <summary>
        /// Token错误
        /// </summary>
        KConnectionStatusTokenIncorrect = -5,

        /// <summary>
        /// 服务器关闭
        /// </summary>
        KConnectionStatusServerDown = -4,

        /// <summary>
        /// 被拒绝
        /// </summary>
        KConnectionStatusRejected = -3,

        /// <summary>
        /// 退出登录
        /// </summary>
        KConnectionStatusLogout = -2,

        /// <summary>
        /// 未连接
        /// </summary>
        KConnectionStatusUnconnected = -1,

        /// <summary>
        /// 连接中
        /// </summary>
        KConnectionStatusConnecting = 0,

        /// <summary>
        /// 已连接
        /// </summary>
        KConnectionStatusConnected = 1,

        /// <summary>
        /// 获取离线消息中，可忽略
        /// </summary>
        KConnectionStatusReceiving = 2
    }

    /// <summary>
    /// 正在输入类型
    /// </summary>
    public enum TypingType
    {
        /// <summary>
        /// 正在输入文本
        /// </summary>
        TypingText = 0,

        /// <summary>
        /// 正在输入语音
        /// </summary>
        TypingVoice = 1,

        /// <summary>
        /// 正在拍摄
        /// </summary>
        TypingCamera = 2,

        /// <summary>
        /// 正在选取位置
        /// </summary>
        TypingLocation = 3,

        /// <summary>
        /// 正在选取文件
        /// </summary>
        TypingFile = 4
    }

    /// <summary>
    /// 消息方向
    /// </summary>
    public enum MessageDirection
    {
        /// <summary>
        /// 当前用户发送的消息
        /// </summary>
        DirectionSend = 0,

        /// <summary>
        /// 当前用户接收的消息
        /// </summary>
        DirectionReceive = 1
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
        MessageContentTypeUnknown = 0,

        /// <summary>
        /// 文本消息
        /// </summary>
        MessageContentTypeText = 1,

        /// <summary>
        /// 语音消息
        /// </summary>
        MessageContentTypeSound = 2,

        /// <summary>
        /// 图片消息
        /// </summary>
        MessageContentTypeImage = 3,

        /// <summary>
        /// 位置消息
        /// </summary>
        MessageContentTypeLocation = 4,

        /// <summary>
        /// 文件消息
        /// </summary>
        MessageContentTypeFile = 5,

        /// <summary>
        /// 视频消息
        /// </summary>
        MessageContentTypeVideo = 6,

        /// <summary>
        /// 动态表情消息
        /// </summary>
        MessageContentTypeSticker = 7,

        /// <summary>
        /// 图文消息
        /// </summary>
        MessageContentTypeLink = 8,

        /// <summary>
        /// 存储不计数文本消息
        /// </summary>
        MessageContentTypePText = 9,

        /// <summary>
        /// 撤回消息
        /// </summary>
        MessageContentTypeRecall = 80,

        /// <summary>
        /// 提醒消息
        /// </summary>
        MessageContentTypeTip = 90,

        /// <summary>
        /// 正在输入消息
        /// </summary>
        MessageContentTypeTyping = 91,

        //通知消息类型

        /// <summary>
        /// 创建群的通知消息
        /// </summary>
        MessageContentTypeCreateGroup = 104,

        /// <summary>
        /// 加群的通知消息
        /// </summary>
        MessageContentTypeAddGroupMember = 105,

        /// <summary>
        /// 踢出群成员的通知消息
        /// </summary>
        MessageContentTypeKickofGroupMember = 106,

        /// <summary>
        /// 退群的通知消息
        /// </summary>
        MessageContentTypeQuitGroup = 107,

        /// <summary>
        /// 解散群的通知消息
        /// </summary>
        MessageContentTypeDismissGroup = 108,

        /// <summary>
        /// 转让群主的通知消息
        /// </summary>
        MessageContentTypeTransferGroupOwner = 109,

        /// <summary>
        /// 修改群名称的通知消息
        /// </summary>
        MessageContentTypeChangeGroupName = 110,

        /// <summary>
        /// 修改群昵称的通知消息
        /// </summary>
        MessageContentTypeModifyGroupAlias = 111,

        /// <summary>
        /// 修改群头像的通知消息
        /// </summary>
        MessageContentTypeChangeGroupPortrait = 112,

        MessageContentTypeChangeMute = 113,
        MessageContentTypeChangeJointype = 114,
        MessageContentTypeChangePrivatechat = 115,
        MessageContentTypeChangeSearchable = 116,
        MessageContentTypeSetManager = 117,
        MessageContentTypeMuteGroupMember = 118,

        /// <summary>
        /// VoIP开始消息
        /// </summary>
        VoipContentTypeStart = 400,
    }

    /// <summary>
    /// 消息存储类型
    /// </summary>
    public enum MessageContentPersistFlag
    {
        /// <summary>
        /// 本地不存储
        /// </summary>
        PersistFlagNotPersist = 0,

        /// <summary>
        /// 本地存储
        /// </summary>
        PersistFlagPersist = 1,

        /// <summary>
        ///  本地存储，并计入未读计数
        /// </summary>
        PersistFlagPersistAndCount = 3,

        /// <summary>
        ///  透传消息，不多端同步，如果对端不在线，消息会丢弃
        /// </summary>
        PersistFlagTransparent = 4,
    }

    public enum MessageStatus
    {
        MessageStatusSending,
        MessageStatusSent,
        MessageStatusSendFailure,
        MessageStatusMentioned,
        MessageStatusAllMentioned,
        MessageStatusUnread,
        MessageStatusReaded,
        MessageStatusPlayed
    }

    #endregion

    public class ChatClient
    {
        static public ChatClient Instance()
        {
            return _instance;
        }

        #region 设置监听

        /// <summary>
        /// 设置连接状态监听，在connect之前调用
        /// </summary>
        /// <param name="listener">连接回调监听</param>
        public void SetConnectionStatusListener(IConnectionStatusListener listener)
        {
            _proto.setConnectStatusListener(listener.OnConnectionStatusChanged);
        }

        /// <summary>
        /// 设置接受消息监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetReceiveMessageListener(IReceiveMessageListener listener)
        {
            _proto.setMessageListener(new ReceiveMessageWrapper(listener).OnReceive, listener.OnRecallMessage, listener.OnDeleteMessage, new MessageDeliveredWrapper(listener).OnReceive, new MessageReadedWrapper(listener).OnReceive);
        }


        /// <summary>
        /// 设置用戶信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetUserInfoUpdateListener(IUserInfoUpdateListener listener)
        {
            _proto.setUserInfoUpdateListener(new UserInfoUpdateWrapper(listener).OnUserInfoUpdated);
        }

        /// <summary>
        /// 设置群組信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetGroupInfoUpdateListener(IGroupInfoUpdateListener listener)
        {
            _proto.setGroupInfoUpdateListener(new GroupInfoUpdateWrapper(listener).OnGroupInfoUpdated);
        }

        /// <summary>
        /// 设置群組成員信息變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetGroupMemberUpdateListener(IGroupMemberUpdateListener listener)
        {
            _proto.setGroupMemberUpdateListener(listener.OnGroupMemberUpdated);
        }

        /// <summary>
        /// 设置聯係人狀態變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetContactUpdateListener(IContactUpdateListener listener)
        {
            _proto.setContactUpdateListener(new ContactUpdateWrapper(listener).OnContactUpdated);
        }

        /// <summary>
        /// 设置好友請求變更监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetFriendRequestUpdateListener(IFriendRequestUpdateListener listener)
        {
            _proto.setFriendRequestUpdateListener(new FriendRequestUpdateWrapper(listener).OnFriendRequestUpdated);
        }

        /// <summary>
        /// 设置設置监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetUserSettingUpdateListener(IUserSettingUpdateListener listener)
        {
            _proto.setUserSettingUpdateListener(listener.OnUserSettingUpdated);
        }

        /// <summary>
        /// 设置頻道信息更新监听，在connect之前调用
        /// </summary>
        /// <param name="listener">监听</param>
        public void SetChannelInfoUpdateListener(IChannelInfoUpdateListener listener)
        {
            _proto.setChannelInfoUpdateListener(new ChannelInfoUpdateWrapper(listener).OnChannelInfoUpdated);
        }

        #endregion

        #region 客户端API

        /// <summary>
        /// 设置自定义消息元宵，在connect之前调用，实现方法请参考文本文件
        /// </summary>
        /// <param name="type">自定义消息原型</param>
        public void RegisterMessage(Type type)
        {
            ContentAttribute attribute = (ContentAttribute)Attribute.GetCustomAttribute(type, typeof(ContentAttribute));
            if (attribute != null)
            {
                _messageContentTypeDict[attribute.Type] = type;
                _proto.registerMessageFlag(attribute.Type, (int)attribute.Flag);
            }
        }

        /// <summary>
        /// 获取当前设备的设备Id
        /// </summary>
        public string GetClientId()
        {
            return _proto.getClientId();
        }

        /// <summary>
        /// 连接IM服务。注意必须getClientId函数获取当前机器的id，然后使用clientId获取token，不然将会连接失败。程序結束前需要調用disconnect。
        /// </summary>
        /// <param name="userId">用户Id</param>
        /// <param name="token">用户令牌</param>
        public bool Connect(string userId, string token)
        {
            RegisterMessage(typeof(TextMessageContent));
            RegisterMessage(typeof(CallStartMessageContent));
            RegisterMessage(typeof(FileMessageContent));
            RegisterMessage(typeof(ImageMessageContent));
            RegisterMessage(typeof(ImageTextMessageContent));
            RegisterMessage(typeof(LocationMessageContent));
            RegisterMessage(typeof(PTextMessageContent));
            RegisterMessage(typeof(SoundMessageContent));
            RegisterMessage(typeof(StickerMessageContent));
            RegisterMessage(typeof(TypingMessageContent));
            RegisterMessage(typeof(VideoMessageContent));

            RegisterMessage(typeof(AddGroupMemberNotificationContent));
            RegisterMessage(typeof(ChangeGroupNameNotificationContent));
            RegisterMessage(typeof(ChangeGroupPortraitNotificationContent));
            RegisterMessage(typeof(CreateGroupNotificationContent));
            RegisterMessage(typeof(DismissGroupNotificationContent));
            RegisterMessage(typeof(GroupJoinTypeNotificationContent));
            RegisterMessage(typeof(GroupMuteNotificationContent));
            RegisterMessage(typeof(GroupMuteNotificationContent));
            RegisterMessage(typeof(GroupPrivateChatNotificationContent));
            RegisterMessage(typeof(GroupSetManagerChatNotificationContent));
            RegisterMessage(typeof(MuteGroupMemberNotification));
            RegisterMessage(typeof(KickoffGroupMemberNotificationContent));
            RegisterMessage(typeof(ModifyGroupAliasNotificationContent));
            RegisterMessage(typeof(QuitGroupNotificationContent));
            RegisterMessage(typeof(RecallMessageContent));
            RegisterMessage(typeof(TipNotificationContent));
            RegisterMessage(typeof(TransferGroupOwnerNotificationContent));

            return _proto.connect(userId, token);
        }

        /// <summary>
        /// 斷開連接
        /// </summary>
        public void Disconnect()
        {
            _proto.disconnect();
        }

        /// <summary>
        /// 当前是否已经调用connect
        /// </summary>
        public bool IsLogined()
        {
            return _proto.isLogined();
        }

        /// <summary>
        /// 获取当前连接状态
        /// </summary>
        public ConnectionStatus GetConnectionStatus()
        {
            return (ConnectionStatus)_proto.getConnectionStatus();
        }

        /// <summary>
        /// 获取当前登录用户的用户Id
        /// </summary>
        public string GetCurrentUserId()
        {
            return _proto.getCurrentUserId();
        }

        /// <summary>
        /// 获取本地时间与服务器时间的差值，精确度不高。
        /// </summary>
        public long GetServerDeltaTime()
        {
            return _proto.getServerDeltaTime();
        }

        #endregion

        #region 会话API

        /// <summary>
        /// 获取会话信息
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <returns>会话信息</returns>
        public List<ConversationInfo> GetConversationInfos(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            string infoStr = _proto.getConversationInfos(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationInfo> cs = JsonConvert.DeserializeObject<List<ConversationInfo>>(infoStr, convert);
            return cs;
        }


        /// <summary>
        /// 获取会话信息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>会话信息</returns>
        public ConversationInfo GetConversationInfo(Conversation conversation)
        {
            string info = _proto.getConversationInfo((int)conversation.Type, conversation.Target, conversation.Line);

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
        public List<ConversationSearchInfo> SearchConversation(string keyword, List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            string infos = _proto.searchConversation(keyword, types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            List<ConversationSearchInfo> cs = JsonConvert.DeserializeObject<List<ConversationSearchInfo>>(infos, convert);
            return cs;
        }

        /// <summary>
        /// 删除会话
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="clearMessage">是否删除会话中的消息</param>
        public void RemoveConversation(Conversation conversation, bool clearMessage)
        {
            _proto.removeConversation((int)conversation.Type, conversation.Target, conversation.Line, clearMessage);
        }

        /// <summary>
        /// 设置或取消会话置顶
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="top">是否置顶</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetConversationTop(Conversation conversation, bool top, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setConversationTop((int)conversation.Type, conversation.Target, conversation.Line, top, () => { succDele(); }, errorCode => { errDele(errorCode); });
        }

        /// <summary>
        /// 设置会话免打扰
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="silent">是否免打扰</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetConversationSilent(Conversation conversation, bool silent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setConversationSilent((int)conversation.Type, conversation.Target, conversation.Line, silent, () => { succDele(); }, errorCode => { errDele(errorCode); });
        }

        /// <summary>
        /// 设置会话草稿
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="draft">草稿</param>
        public void SetConversationDraft(Conversation conversation, string draft)
        {
            _proto.setConversationDraft((int)conversation.Type, conversation.Target, conversation.Line, draft);
        }

        /// <summary>
        /// 获取指定类型会话的未读数
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        /// <returns>未读数</returns>
        public UnreadCount GetUnreadCount(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            string unreadStr = _proto.getUnreadCount(types, lines);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /// <summary>
        /// 获取某个会话的未读数
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>未读数</returns>
        public UnreadCount GetUnreadCount(Conversation conversation)
        {
            string unreadStr = _proto.getUnreadCount((int)conversation.Type, conversation.Target, conversation.Line);

            WfcJsonConverter convert = new WfcJsonConverter();
            UnreadCount uc = JsonConvert.DeserializeObject<UnreadCount>(unreadStr, convert);
            return uc;
        }

        /// <summary>
        /// 清空会话未读数
        /// </summary>
        /// <param name="conversation">会话</param>
        public void ClearUnreadStatus(Conversation conversation)
        {
            _proto.clearUnreadStatus((int)conversation.Type, conversation.Target, conversation.Line);
        }

        /// <summary>
        /// 清空会话类型的未读数
        /// </summary>
        /// <param name="conversationTypes">会话类型</param>
        /// <param name="lines">默认传</param>
        public void ClearUnreadStatus(List<ConversationType> conversationTypes, List<int> lines)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            _proto.clearUnreadStatus(types, lines);
        }

        /// <summary>
        /// 清空所有会话的未读数
        /// </summary>
        public void ClearAllUnreadStatus()
        {
            _proto.clearAllUnreadStatus();
        }

        /// <summary>
        /// 获取某个会话的送达状态
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>会话的送达状态</returns>
        public Dictionary<string, long> GetMessageDelivery(Conversation conversation)
        {
            WfcJsonConverter convert = new WfcJsonConverter();
            return JsonConvert.DeserializeObject<Dictionary<string, long>>(_proto.getMessageDelivery((int)conversation.Type, conversation.Target), convert);
        }

        /// <summary>
        /// 获取某个会话的已读状态
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <returns>会话已读状态</returns>
        public Dictionary<string, long> GetConversationRead(Conversation conversation)
        {
            WfcJsonConverter convert = new WfcJsonConverter();
            return JsonConvert.DeserializeObject<Dictionary<string, long>>(_proto.getConversationRead((int)conversation.Type, conversation.Target, conversation.Line), convert);
        }

        #endregion

        #region 消息API

        /// <summary>
        /// 设置媒体消息已播放
        /// </summary>
        /// <param name="messageId">消息ID</param>
        public void SetMediaMessagePlayed(long messageId)
        {
            _proto.setMediaMessagePlayed((int)messageId);
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="contentTypes">消息类型</param>
        /// <param name="fromIndex">起始index</param>
        /// <param name="count">总数</param>
        /// <param name="user">用户</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> GetMessages(Conversation conversation, List<int> contentTypes, long fromIndex, int count, string user)
        {
            string messagesStr = _proto.getMessages((int)conversation.Type, conversation.Target, conversation.Line, contentTypes, fromIndex, count, user);

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
        /// <param name="user">用户</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> GetMessages(List<ConversationType> conversationTypes, List<int> lines, List<int> contentTypes, long fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            string messagesStr = _proto.getMessages(types, lines, contentTypes, fromIndex, count, user);

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
        /// <param name="user">用户</param>
        /// <returns>消息实体</returns>
        public List<MessageEx> GetMessagesByMessageStatus(List<ConversationType> conversationTypes, List<int> lines, List<MessageStatus> messageStatus, long fromIndex, int count, string user)
        {
            List<int> types = new List<int>();
            foreach (var ct in conversationTypes)
            {
                types.Add((int)ct);
            }

            List<int> ss = new List<int>();
            foreach (var ct in messageStatus)
            {
                ss.Add((int)ct);
            }

            string messagesStr = _proto.getMessagesByMessageStatus(types, lines, ss, fromIndex, count, user);

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
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void GetRemoteMessages(Conversation conversation, List<int> contentTypes, long beforeMessageUid, int count, OnGetRemoteMessageDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.getRemoteMessages((int)conversation.Type, conversation.Target, conversation.Line, contentTypes, beforeMessageUid, count, messages =>
           {
               WfcJsonConverter convert = new WfcJsonConverter();
               List<MessageEx> ms = JsonConvert.DeserializeObject<List<MessageEx>>(messages, convert);
               succDele(ms);
           }, errorCode => { errDele(errorCode); });
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <returns>消息实体</returns>
        public MessageEx GetMessage(long messageId)
        {
            string messageStr = _proto.getMessage((int)messageId);

            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 获取消息
        /// </summary>
        /// <param name="messageUid">消息UID</param>
        /// <returns>消息实体</returns>
        public MessageEx GetMessageByUid(long messageUid)
        {
            string messageStr = _proto.getMessageByUid(messageUid);

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
        public List<MessageEx> SearchMessage(Conversation conversation, string keyword, int count)
        {
            string messagesStr = _proto.searchMessage((int)conversation.Type, conversation.Target, conversation.Line, keyword, count);

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
        /// <param name="succDele">成功回调</param>
        /// <param name="progressDele">进度回调</param>
        /// <param name="errDele">错误回调</param>
        /// <returns>消息实体</returns>
        public MessageEx SendMessage(Conversation conversation, MessageContent content, List<string> toUsers, int expireDuration, onBigIntBigIntCallbackDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = _proto.sendMessage((int)conversation.Type, conversation.Target, conversation.Line, contentStr, toUsers, expireDuration, succDele, progressDele, errDele);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 撤回消息
        /// </summary>
        /// <param name="messageUid">待撤回的消息Uid</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void RecallMessage(long messageUid, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.recallMessage(messageUid, succDele, errDele);
        }

        /// <summary>
        /// 上传媒体(图片、语音、文件等)
        /// </summary>
        /// <param name="fileName">文件名，可为空</param>
        /// <param name="mediaData">媒体信息, 经过Base64编码</param>
        /// <param name="mediaType">媒体类型</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="progressDele">进度回调</param>
        /// <param name="errDele">错误回调</param>
        public void UploadMedia(string fileName, string mediaData, MediaType mediaType, OnUploadedMediaDelegate succDele, onIntIntCallbackDelegate progressDele, onErrorCallbackDelegate errDele)
        {
            _proto.uploadMedia(fileName, mediaData, (int)mediaType, remoteUrl => { succDele(remoteUrl); }, progressDele, errDele);
        }

        /// <summary>
        /// 删除消息
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <returns>是否删除成功</returns>
        public bool DeleteMessage(long messageId)
        {
            return _proto.deleteMessage((int)messageId);
        }

        /// <summary>
        /// 删除会话中的消息
        /// </summary>
        /// <param name="conversation">会话</param>
        public void ClearMessages(Conversation conversation)
        {
            _proto.clearMessages((int)conversation.Type, conversation.Target, conversation.Line);
        }

        /// <summary>
        /// 删除会话中的before之前的旧消息。
        /// </summary>
        /// <param name="conversation">会话，如果conversation为nil，则清除所有会话的消息。</param>
        /// <param name="before">时间点，单位是毫秒</param>
        public void ClearMessages(Conversation conversation, long before)
        {
            _proto.clearMessages((int)conversation.Type, conversation.Target, conversation.Line, before);
        }

        /// <summary>
        /// 插入消息
        /// </summary>
        /// <param name="conversation">会话</param>
        /// <param name="sender">发送者</param>
        /// <param name="content">消息内容</param>
        /// <param name="status">消息状态，注意消息状态会影响消息方向</param>
        /// <param name="notify">是否通知</param>
        /// <param name="serverTime">时间，0为当前时间</param>
        /// <returns>消息实体</returns>
        public MessageEx InsertMessage(Conversation conversation, string sender, MessageContent content, MessageStatus status, bool notify, long serverTime)
        {
            var contentStr = JsonTools.Stringfy(content);
            string messageStr = _proto.insert((int)conversation.Type, conversation.Target, conversation.Line, sender, contentStr, (int)status, notify, serverTime);
            WfcJsonConverter convert = new WfcJsonConverter();
            MessageEx ms = JsonConvert.DeserializeObject<MessageEx>(messageStr, convert);
            return ms;
        }

        /// <summary>
        /// 更新消息内容
        /// </summary>
        /// <param name="messageId">消息ID</param>
        /// <param name="content">消息内容</param>
        public void UpdateMessage(long messageId, MessageContent content)
        {
            var contentStr = JsonTools.Stringfy(content);
            _proto.updateMessage((int)messageId, contentStr);
        }

        #endregion

        #region 用户API

        /// <summary>
        /// 获取用户信息
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。</param>
        /// <returns>本地的用户信息，可能为空</returns>
        public UserInfo GetUserInfo(string userId, bool refresh)
        {
            string userStr = _proto.getUserInfo(userId, refresh);
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
        public UserInfo GetUserInfo(string userId, string groupId, bool refresh)
        {
            string userStr = _proto.getUserInfo(userId, groupId, refresh);
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
        public List<UserInfo> GetUserInfos(List<string> userIds, string groupId)
        {
            string usersStr = _proto.getUserInfos(userIds, groupId);
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
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SearchUser(string keyword, SearchUserType searchType, int page, OnSearchUsersDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.searchUser(keyword, (int)searchType, page, usersStr =>
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
        public bool IsMyFriend(string userId)
        {
            return _proto.isMyFriend(userId);
        }

        /// <summary>
        /// 获取当前用户的好友列表
        /// </summary>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>好友列表的用户ID</returns>
        public List<string> GetMyFriendList(bool refresh)
        {
            string friendsStr = _proto.getMyFriendList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }


        /// <summary>
        /// 搜索好友
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <returns>好友用户信息</returns>
        public List<UserInfo> SearchFriends(string keyword)
        {
            string usersStr = _proto.searchFriends(keyword);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<UserInfo> us = JsonConvert.DeserializeObject<List<UserInfo>>(usersStr, convert);
            return us;
        }

        /// <summary>
        /// 获取收到的好友请求
        /// </summary>
        /// <returns>好友请求</returns>
        public List<FriendRequest> GetIncommingFriendRequest()
        {
            string usersStr = _proto.getIncommingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /// <summary>
        /// 获取发出的好友请求
        /// </summary>
        /// <returns>好友请求</returns>
        public List<FriendRequest> GetOutgoingFriendRequest()
        {
            string usersStr = _proto.getOutgoingFriendRequest();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<FriendRequest> gs = JsonConvert.DeserializeObject<List<FriendRequest>>(usersStr, convert);
            return gs;
        }

        /// <summary>
        /// 从服务器更新好友请求
        /// </summary>
        public void LoadFriendRequestFromRemote()
        {
            _proto.loadFriendRequestFromRemote();
        }

        /// <summary>
        /// 获取未读的好友请求数
        /// </summary>
        /// <returns>未读的好友请求数</returns>
        public int GetUnreadFriendRequestStatus()
        {
            return _proto.getUnreadFriendRequestStatus();
        }

        /// <summary>
        /// 清除好友请求的未读数
        /// </summary>
        public void ClearUnreadFriendRequestStatus()
        {
            _proto.clearUnreadFriendRequestStatus();
        }

        /// <summary>
        /// 删除好友
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void DeleteFriend(string userId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.deleteFriend(userId, succDele, errDele);
        }

        /// <summary>
        /// 发送好友请求
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="reason">请求说明</param>
        /// <param name="extra">请求Extra</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SendFriendRequest(string userId, string reason, string extra, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.sendFriendRequest(userId, reason, extra, succDele, errDele);
        }

        /// <summary>
        /// 处理好友请求
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="accpet">是否接受</param>
        /// <param name="friendExtra">extra</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void HandleFriendRequest(string userId, bool accpet, string friendExtra, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.handleFriendRequest(userId, accpet, friendExtra, succDele, errDele);
        }

        /// <summary>
        /// 获取用户的别名
        /// </summary>
        /// <param name="userId">用户ID</param>
        public string GetFriendAlias(string userId)
        {
            return _proto.getFriendAlias(userId);
        }

        /// <summary>
        /// 设置用户的别名
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="alias">别名</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetFriendAlias(string userId, string alias, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setFriendAlias(userId, alias, succDele, errDele);
        }

        /// <summary>
        /// 查询用户是否被加入黑名单
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <returns>是否被加入黑名单</returns>
        public bool IsBlackListed(string userId)
        {
            return _proto.isBlackListed(userId);
        }

        /// <summary>
        /// 获取当前用户的黑名单列表
        /// </summary>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>黑名单列表的用户ID</returns>
        public List<string> GetBlackList(bool refresh)
        {
            string friendsStr = _proto.getBlackList(refresh);
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(friendsStr, convert);
            return us;
        }

        /// <summary>
        /// 设置黑名单
        /// </summary>
        /// <param name="userId">用户ID</param>
        /// <param name="isBlackListed">YES</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetBlackList(string userId, bool isBlackListed, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setBlackList(userId, isBlackListed, succDele, errDele);
        }

        #endregion

        #region 群组API

        /// <summary>
        /// 搜索群组
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <returns>群组搜索结果</returns>
        public List<GroupSearchInfo> SearchGroups(string keyword)
        {
            string usersStr = _proto.searchGroups(keyword);
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
        public List<GroupMember> GetGroupMembers(string groupId, bool forceUpdate)
        {
            string membersStr = _proto.getGroupMembers(groupId, forceUpdate);
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
        public GroupInfo GetGroupInfo(string groupId, bool refresh)
        {
            string gStr = _proto.getGroupInfo(groupId, refresh);
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
        public GroupMember GetGroupMember(string groupId, string memberId)
        {
            string memberStr = _proto.getGroupMember(groupId, memberId);
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
        /// <param name="type">群类型</param>
        /// <param name="groupExtra">群Extra</param>
        /// <param name="groupMembers">群成员</param>
        /// <param name="memberExtra">群成员Extra</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void CreateGroup(string groupId, string groupName, string groupPortrait, GroupType type, string groupExtra, List<string> groupMembers, string memberExtra, List<int> notifyLines, MessageContent notifyContent, OnCreateGroupDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.createGroup(groupId, groupName, groupPortrait, (int)type, groupExtra, groupMembers, memberExtra, notifyLines, contentStr, gid => { succDele(gid); }, errDele);
        }

        /// <summary>
        /// 添加群成员
        /// </summary>
        /// <param name="members">成员的用户ID列表</param>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void AddMembers(List<string> members, string groupId, string memberExtra, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.addMembers(members, groupId, memberExtra, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 踢出群成员
        /// </summary>
        /// <param name="members">成员的用户ID列表</param>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void KickoffMembers(List<string> members, string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.kickoffMembers(members, groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 退群
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void QuitGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.quitGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 解散群
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void DismissGroup(string groupId, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.dismissGroup(groupId, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 修改群信息
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="type">要修改的群属性</param>
        /// <param name="newValue">要修改的群属性值</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void ModifyGroupInfo(string groupId, ModifyGroupInfoType type, string newValue, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.modifyGroupInfo(groupId, (int)type, newValue, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 修改群昵称
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="newAlias">昵称</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void ModifyGroupAlias(string groupId, string newAlias, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.modifyGroupAlias(groupId, newAlias, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 转移群主
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="newOwner">群主的用户ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void TransferGroup(string groupId, string newOwner, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.transferGroup(groupId, newOwner, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 设置群管理
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="isSet">设置或取消</param>
        /// <param name="memberIds">成员ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetGroupManager(string groupId, bool isSet, List<string> memberIds, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.setGroupManager(groupId, isSet, memberIds, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 设置群成员禁言
        /// </summary>
        /// <param name="groupId">群ID</param>
        /// <param name="isSet">设置或取消</param>
        /// <param name="memberIds">成员ID</param>
        /// <param name="notifyLines">默认传</param>
        /// <param name="notifyContent">通知消息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void MuteGroupMember(string groupId, bool isSet, List<string> memberIds, List<int> notifyLines, MessageContent notifyContent, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            var contentStr = JsonTools.Stringfy(notifyContent);
            _proto.muteGroupMember(groupId, isSet, memberIds, notifyLines, contentStr, succDele, errDele);
        }

        /// <summary>
        /// 获取当前用户收藏的群组
        /// </summary>
        /// <returns>当前用户收藏的群组ID</returns>
        public List<string> GetFavGroups()
        {
            string membersStr = _proto.getFavGroups();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 是否是当前用户收藏的群组
        /// </summary>
        /// <returns>是否是当前用户收藏的群组</returns>
        public bool IsFavGroup(string groupId)
        {
            return _proto.isFavGroup(groupId);
        }

        /// <summary>
        /// 设置群组收藏状态
        /// </summary>
        /// <param name="groupId">群组ID</param>
        /// <param name="fav">是否收藏</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetFavGroup(string groupId, bool fav, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setFavGroup(groupId, fav, succDele, errDele);
        }

        #endregion

        #region 个人设置API

        /// <summary>
        /// 获取个人设置
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <param name="key">设置项的key</param>
        /// <returns>设置值</returns>
        public string GetUserSetting(UserSettingScope scope, string key)
        {
            return _proto.getUserSetting((int)scope, key);
        }

        /// <summary>
        /// 获取个人一类设置
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <returns>scope对应的所有设置值</returns>
        public Dictionary<string, string> GetUserSettings(UserSettingScope scope)
        {
            return null;
        }

        /// <summary>
        /// 设置个人设置项
        /// </summary>
        /// <param name="scope">设置项的scope</param>
        /// <param name="key">设置项的key</param>
        /// <param name="value">值</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetUserSetting(UserSettingScope scope, string key, string value, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setUserSetting((int)scope, key, value, succDele, errDele);
        }

        /// <summary>
        /// 修改个人信息
        /// </summary>
        /// <param name="values">信息</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void ModifyMyInfo(Dictionary<int, string> values, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.modifyMyInfo(values, succDele, errDele);
        }

        /// <summary>
        /// 是否是全局禁止通知
        /// </summary>
        public bool IsGlobalSlient()
        {
            return _proto.isGlobalSlient();
        }

        /// <summary>
        /// 设置全局禁止通知
        /// </summary>
        /// <param name="slient">是否禁止通知</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetGlobalSlient(bool slient, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setGlobalSlient(slient, succDele, errDele);
        }

        /// <summary>
        /// 通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
        /// </summary>
        public bool IsHiddenNotificationDetail()
        {
            return _proto.isHiddenNotificationDetail();
        }

        /// <summary>
        /// 设置通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
        /// </summary>
        /// <param name="hidden">是否隐藏详情</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetHiddenNotificationDetail(bool hidden, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setHiddenNotificationDetail(hidden, succDele, errDele);
        }

        /// <summary>
        /// 群聊中是否显示群成员名称
        /// </summary>
        /// <param name="hidden">是否显示</param>
        /// <param name="groupId">群组ID</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SetHiddenGroupMemberName(bool hidden, string groupId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.setHiddenGroupMemberName(hidden, groupId, succDele, errDele);
        }

        #endregion

        #region 聊天室API

        /// <summary>
        /// 加入聊天室
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void JoinChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.joinChatroom(chatroomId, succDele, errDele);
        }

        /// <summary>
        /// 退出聊天室
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void QuitChatroom(string chatroomId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.quitChatroom(chatroomId, succDele, errDele);
        }

        /// <summary>
        /// 获取聊天室信息
        /// </summary>
        /// <param name="chatroomId">聊天室ID</param>
        /// <param name="updateDt">上次聊天室获取时间戳，可以为0</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void GetChatroomInfo(string chatroomId, long updateDt, OnGetChatroomInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.getChatroomInfo(chatroomId, updateDt, str =>
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
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void GetChatroomMemberInfo(string chatroomId, int maxCount, OnGetChatroomMemberInfoDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.getChatroomMemberInfo(chatroomId, maxCount, str =>
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
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void CreateChannel(string channelName, string channelPortrait, int status, string desc, string extra, onGeneralStringSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.createChannel(channelName, channelPortrait, status, desc, extra, succDele, errDele);
        }

        /// <summary>
        /// 获取频道信息
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="refresh">是否强制从服务器更新，如果不刷新则从本地缓存中读取</param>
        /// <returns>群信息</returns>
        public ChannelInfo GetChannelInfo(string channelId, bool refresh)
        {
            string str = _proto.getChannelInfo(channelId, refresh);
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
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void ModifyChannelInfo(string channelId, ModifyChannelInfoType type, string newValue, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.modifyChannelInfo(channelId, (int)type, newValue, succDele, errDele);
        }

        /// <summary>
        /// 搜索频道
        /// </summary>
        /// <param name="keyword">关键词</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void SearchChannel(string keyword, OnSearchChannelsDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.searchChannel(keyword, str =>
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
        public bool IsListenedChannel(string channelId)
        {
            return _proto.isListenedChannel(channelId);
        }

        /// <summary>
        /// 收听或者取消收听频道
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="listen">是否收听</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void ListenChannel(string channelId, bool listen, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.listenChannel(channelId, listen, succDele, errDele);
        }

        /// <summary>
        /// 获取当前用户创建的频道
        /// </summary>
        /// <returns>当前用户创建的频道ID</returns>
        public List<string> GetMyChannels()
        {
            string membersStr = _proto.getMyChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 获取当前用户收听的频道
        /// </summary>
        /// <returns>当前用户收听的频道ID</returns>
        public List<string> GetListenedChannels()
        {
            string membersStr = _proto.getListenedChannels();
            WfcJsonConverter convert = new WfcJsonConverter();
            List<string> us = JsonConvert.DeserializeObject<List<string>>(membersStr, convert);
            return us;
        }

        /// <summary>
        /// 销毁频道
        /// </summary>
        /// <param name="channelId">频道ID</param>
        /// <param name="succDele">成功回调</param>
        /// <param name="errDele">错误回调</param>
        public void DestoryChannel(string channelId, onGeneralVoidSuccessCallbackDelegate succDele, onErrorCallbackDelegate errDele)
        {
            _proto.destoryChannel(channelId, succDele, errDele);
        }

        #endregion

        class ReceiveMessageWrapper
        {
            public ReceiveMessageWrapper(IReceiveMessageListener listener)
            {
                _mListener = listener;
            }

            private IReceiveMessageListener _mListener;

            public void OnReceive(string messages, bool hasMore)
            {
                List<MessageEx> ms = JsonTools.Jsonfy<List<MessageEx>>(messages);
                _mListener.OnReceiveMessages(ms, hasMore);
            }
        }

        class MessageDeliveredWrapper
        {
            public MessageDeliveredWrapper(IReceiveMessageListener listener)
            {
                _mListener = listener;
            }

            private IReceiveMessageListener _mListener;

            public void OnReceive(string str)
            {
                WfcJsonConverter convert = new WfcJsonConverter();
                Dictionary<string, long> ms = JsonConvert.DeserializeObject<Dictionary<string, long>>(str, convert);
                _mListener.OnMessageDeliveried(ms);
            }
        }

        class MessageReadedWrapper
        {
            public MessageReadedWrapper(IReceiveMessageListener listener)
            {
                _mListener = listener;
            }

            private IReceiveMessageListener _mListener;

            public void OnReceive(string str)
            {
                List<ReadEntry> ms = JsonTools.Jsonfy<List<ReadEntry>>(str);
                _mListener.OnMessageReaded(ms);
            }
        }

        class UserInfoUpdateWrapper
        {
            public UserInfoUpdateWrapper(IUserInfoUpdateListener listener)
            {
                _mListener = listener;
            }

            private IUserInfoUpdateListener _mListener;

            public void OnUserInfoUpdated(string users)
            {
                List<UserInfo> userInfos = JsonTools.Jsonfy<List<UserInfo>>(users);
                _mListener.OnUserInfoUpdated(userInfos);
            }
        }

        class GroupInfoUpdateWrapper
        {
            public GroupInfoUpdateWrapper(IGroupInfoUpdateListener listener)
            {
                _mListener = listener;
            }

            private IGroupInfoUpdateListener _mListener;

            public void OnGroupInfoUpdated(string groups)
            {
                List<GroupInfo> groupInfos = JsonTools.Jsonfy<List<GroupInfo>>(groups);
                _mListener.OnGroupInfoUpdated(groupInfos);
            }
        }

        class ContactUpdateWrapper
        {
            public ContactUpdateWrapper(IContactUpdateListener listener)
            {
                _mListener = listener;
            }

            private IContactUpdateListener _mListener;

            public void OnContactUpdated(string groups)
            {
                List<string> friends = JsonTools.Jsonfy<List<string>>(groups);
                _mListener.OnContactUpdated(friends);
            }
        }

        class FriendRequestUpdateWrapper
        {
            public FriendRequestUpdateWrapper(IFriendRequestUpdateListener listener)
            {
                _mListener = listener;
            }

            private IFriendRequestUpdateListener _mListener;

            public void OnFriendRequestUpdated(string groups)
            {
                List<string> friends = JsonTools.Jsonfy<List<string>>(groups);
                _mListener.OnFriendRequestUpdated(friends);
            }
        }

        class ChannelInfoUpdateWrapper
        {
            public ChannelInfoUpdateWrapper(IChannelInfoUpdateListener listener)
            {
                _mListener = listener;
            }

            private IChannelInfoUpdateListener _mListener;

            public void OnChannelInfoUpdated(string groups)
            {
                List<ChannelInfo> groupInfos = JsonTools.Jsonfy<List<ChannelInfo>>(groups);
                _mListener.OnChannelInfoUpdated(groupInfos);
            }
        }


        public MessageContent GetContent(MessagePayload payload)
        {
            MessageContent content;
            if (_messageContentTypeDict.ContainsKey(payload.ContentType))
            {
                Type type = _messageContentTypeDict[payload.ContentType];
                content = (MessageContent)Activator.CreateInstance(type);
                content.Extra = payload.Extra;
                content.MentionedTargets = payload.MentionedTargets;
                content.MentionedType = payload.MentionedType;
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
                content = new UnknownMessageContent();
                //When decode failure, fallback to unknown message.
                content.Decode(payload);
            }

            return content;
        }

        private Proto _proto = new Proto();
        private static ChatClient _instance = new ChatClient();
        private Dictionary<int, Type> _messageContentTypeDict = new Dictionary<int, Type>();
    }

    public delegate void OnGetRemoteMessageDelegate(List<MessageEx> messages);

    public delegate void OnUploadedMediaDelegate(string remoteUrl);

    public delegate void OnSearchUsersDelegate(List<UserInfo> users);

    public delegate void OnCreateGroupDelegate(string groupId);

    public delegate void OnGetChatroomInfoDelegate(ChatroomInfo chatroomInfo);

    public delegate void OnGetChatroomMemberInfoDelegate(ChatroomMemberInfo memberInfo);

    public delegate void OnSearchChannelsDelegate(List<ChannelInfo> channelInfos);
}