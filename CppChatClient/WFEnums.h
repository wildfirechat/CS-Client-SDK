//
//  WFEnums.h
//  ChatClient
//
//  Created by Hao Jia on 2020/1/30.
//  Copyright © 2020 WF Chat. All rights reserved.
//

#ifndef WFEnums_h
#define WFEnums_h


/**
 会话类型

 - Single_Type: 单聊
 - Group_Type: 群组
 - Chatroom_Type: 聊天室
 - Channel_Type: 频道
 */
enum ConversationType {
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
enum SearchUserType {
    SearchUserType_General,
    SearchUserType_Name_Mobile,
    SearchUserType_Name,
    SearchUserType_Mobile
};

/**
搜索用户类型

- GroupType_Normal: 微信风格群组
- GroupType_Free: 自由风格
- GroupType_Restricted: 带有群管理的群，建议用这个
*/

enum GroupType {
    GroupType_Normal,
    GroupType_Free,
    GroupType_Restricted,
};

enum UserSettingScope {
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
enum ModifyMyInfoType {
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

enum ModifyGroupInfoType {
    Modify_Group_Name = 0,
    Modify_Group_Portrait = 1,
    Modify_Group_Extra = 2,
    Modify_Group_Mute = 3,
    Modify_Group_JoinType = 4,
    Modify_Group_PrivateChat = 5,
    Modify_Group_Searchable = 6
};


enum ModifyChannelInfoType {
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
enum MediaType {
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

 - kConnectionStatusTimeInconsistent 服务器和客户端时间相差太大
 - kConnectionStatusNotLicensed  专业版IM服务没有授权或者授权过期，社区版不会有此状态
 - kConnectionStatusKickedoff 多端登录被迫下线。
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
enum ConnectionStatus {
  kConnectionStatusTimeInconsistent = -9,
  kConnectionStatusNotLicensed = -8,
  //错误码kConnectionStatusKickedoff是IM服务2021.9.15之后的版本才支持，并且打开服务器端开关server.client_support_kickoff_event
  kConnectionStatusKickedoff = -7,
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
enum TypingType {
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
enum MessageDirection {
    Direction_Send = 0,
    Direction_Receive = 1
};

enum MessageContentType {
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
enum MessageContentPersistFlag {
    PersistFlag_NOT_PERSIST = 0,
    PersistFlag_PERSIST = 1,
    PersistFlag_PERSIST_AND_COUNT = 3,
    PersistFlag_TRANSPARENT = 4,
};

#endif /* WFEnums_h */
