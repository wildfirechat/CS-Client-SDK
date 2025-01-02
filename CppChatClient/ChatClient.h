#pragma once
#include <string>
#include <map>
#include "message/Message.h"
#include "message/MessageContent.h"
#include "model/ConversationInfo.h"
#include "model/ConversationSearchInfo.h"
#include "model/UserInfo.h"
#include "WFEnums.h"
#include "model/GroupSearchInfo.h"
#include "model/FriendRequest.h"
#include "model/ChatroomInfo.h"
#include "model/ChannelInfo.h"

namespace WFCLib {

/*
 全局状态监听，建议程序启动时设置
 */

/*
 连接状态监听
 */
class ConnectionStatusListener {
public:
    ConnectionStatusListener() {}
    virtual void onConnectionStatusChanged(ConnectionStatus status) = 0;
    virtual ~ConnectionStatusListener() {}
};

/*
 消息监听
 */
class ReceiveMessageListener {
public:
    ReceiveMessageListener() {}
    virtual void onReceiveMessages(const std::list<Message> &messages, bool hasMore) = 0;
    virtual void onRecallMessage(const std::string &operatorId, int64_t messageUid) = 0;
	virtual void onDeleteMessage(int64_t messageUid) = 0;
    virtual ~ReceiveMessageListener() {}
};

/*
 用户信息变更监听
 */
class UserInfoUpdateListener {
public:
    UserInfoUpdateListener() {}
    virtual ~UserInfoUpdateListener() {}
    
    virtual void onUserInfoUpdated(const std::list<UserInfo> &userInfos) = 0;
};

/*
群组信息变更监听
*/
class GroupInfoUpdateListener {
public:
    GroupInfoUpdateListener() {}
    virtual ~GroupInfoUpdateListener() {}
    
    virtual void onGroupInfoUpdated(const std::list<GroupInfo> &groupInfos) = 0;
};

/*
群组成员变更监听
*/
class GroupMemberUpdateListener {
public:
    GroupMemberUpdateListener() {}
    virtual ~GroupMemberUpdateListener() {}
    
    virtual void onGroupMemberUpdated(const std::string &groupId) = 0;
};

/*
 联系人状态监听
 */
class ContactUpdateListener {
public:
    ContactUpdateListener() {}
    virtual ~ContactUpdateListener() {}
    
    virtual void onContactUpdated(const std::list<std::string> &friendUids) = 0;
};

/*
 好友请求状态变更坚挺
 */
class FriendRequestUpdateListener {
public:
    FriendRequestUpdateListener() {}
    virtual ~FriendRequestUpdateListener() {}
    
    virtual void onFriendRequestUpdated(const std::list<std::string> &newRequests) = 0;
};

/*
 用户设置监听
 */
class UserSettingUpdateListener {
public:
    UserSettingUpdateListener() {}
    virtual ~UserSettingUpdateListener() {}
    
    virtual void onUserSettingUpdated() = 0;
};

/*
 频道信息变更监听
 */
class ChannelInfoUpdateListener {
public:
    ChannelInfoUpdateListener() {}
    virtual ~ChannelInfoUpdateListener() {}
    
    virtual void onChannelInfoUpdated(const std::list<ChannelInfo> &channelInfo) = 0;
};


/**
 事件回调，一般都是一次性的。
 */

/*
 通用的void的事件回调
 */
class GeneralVoidCallback {
public:
    GeneralVoidCallback() {}
    virtual ~GeneralVoidCallback() {}

    virtual void onSuccess() = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
通用的string的事件回调
*/
class GeneralStringCallback {
public:
    GeneralStringCallback() {}
    virtual ~GeneralStringCallback() {}

    virtual void onSuccess(const std::string &value) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 获取远程历史消息回调
 */
class GetRemoteMessageCallback {
public:
    GetRemoteMessageCallback() {}
    virtual ~GetRemoteMessageCallback() {}

    virtual void onSuccess(const std::list<Message> &messages) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 发送消息回调
 */
class WFSendMessageCallback {
public:
    WFSendMessageCallback() {}
    virtual ~WFSendMessageCallback() {}

    virtual void onSuccess(int64_t messageUid, int64_t timestamp) = 0;
    // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
	virtual void onPrepared(int messageId, int64_t timestamp) = 0;
    virtual void onProgress(int uploaded, int total) = 0;
	virtual void onUploaded(const std::string &remoteUrl) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 搜索用户回调
 */
class SearchUserCallback {
public:
    SearchUserCallback() {}
    virtual ~SearchUserCallback() {}

    virtual void onSuccess(const std::list<UserInfo> &messages) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 获取聊天室信息回调
 */
class GetChatroomInfoCallback {
public:
    GetChatroomInfoCallback() {}
    virtual ~GetChatroomInfoCallback() {}

    virtual void onSuccess(const ChatroomInfo &chatroomInfo) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 获取聊天室成员信息回调
 */
class GetChatroomMemberInfoCallback {
public:
    GetChatroomMemberInfoCallback() {}
    virtual ~GetChatroomMemberInfoCallback() {}

    virtual void onSuccess(const ChatroomMemberInfo &chatroomMemberInfo) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 获取频道信息回调
 */
class GetChannelInfoCallback {
public:
    GetChannelInfoCallback() {}
    virtual ~GetChannelInfoCallback() {}

    virtual void onSuccess(const ChannelInfo &channelInfo) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 搜索频道回调
 */
class SearchChannelCallback {
public:
    SearchChannelCallback() {}
    virtual ~SearchChannelCallback() {}

    virtual void onSuccess(const std::list<ChannelInfo> &channels) = 0;
    virtual void onFailure(int errorCode) = 0;
};

/*
 上传媒体文件回调
 */
class UploadMediaCallback {
public:
    UploadMediaCallback() {}
    virtual ~UploadMediaCallback() {}

    virtual void onSuccess(const std::string &remoteUrl) = 0;
    // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
    virtual void onProgress(int uploaded, int total) = 0;
    virtual void onFailure(int errorCode) = 0;
};

class ChatClient
{
public:
    static ChatClient* Instance();

    /**
     设置连接状态监听，在connect之前调用

     @param listener 连接回调监听
     */
    void setConnectionStatusListener(ConnectionStatusListener *listener);

    /**
    设置接受消息监听，在connect之前调用

    @param listener 接受消息监听
    */
    void setReceiveMessageListener(ReceiveMessageListener *listener);

	/**
	设置用戶信息變更监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setUserInfoUpdateListener(UserInfoUpdateListener *listener);

	/**
	设置群組信息變更监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setGroupInfoUpdateListener(GroupInfoUpdateListener *listener);

	/**
	设置群組成員信息變更监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setGroupMemberUpdateListener(GroupMemberUpdateListener *listener);

	/**
	设置聯係人狀態變更监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setContactUpdateListener(ContactUpdateListener *listener);

	/**
	设置好友請求變更监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setFriendRequestUpdateListener(FriendRequestUpdateListener *listener);

	/**
	设置設置监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setUserSettingUpdateListener(UserSettingUpdateListener *listener);

	/**
	设置頻道信息监听，在connect之前调用

	@param listener 接受消息监听
	*/
	void setChannelInfoUpdateListener(ChannelInfoUpdateListener *listener);

    /**
    设置自定义消息元宵，在connect之前调用，实现方法请参考文本文件

    @param prototype 自定义消息原型
    */
    void registerMessage(const MessageContentPrototype *prototype);

	/**
	设置应用名称，应用数据会保存在用户数据应用名称下，请使用英文

	@param appName 应用名
	*/
	void setAppName(const std::string &appName);

    /**
     获取当前设备的设备Id
     */
    const std::string getClientId();

    /**
     连接IM服务。注意必须getClientId函数获取当前机器的id，然后使用clientId获取token，不然将会连接失败。程序結束前需要調用disconnect。

     @param userId 用户Id
     @param token 用户令牌
     */
    int64_t connect(const std::string & userId, const std::string &token);

    /**
    斷開連接
    */
    bool disconnect();
    /**
     当前是否已经调用connect
     */
    bool isLogined();

    /**
     获取当前连接状态
     */
    ConnectionStatus getConnectionStatus();

    /**
     获取当前登录用户的用户Id
     */
    const std::string getCurrentUserId();

    /**
    获取本地时间与服务器时间的差值，精确度不高。
     */
    int64_t getServerDeltaTime();


    /**
     获取会话信息

     @param conversationTypes 会话类型
     @param lines 默认传 @[@(0)]
     @return 会话信息
     */
    const std::list<ConversationInfo> getConversationInfos(const std::list<int> &conversationTypes, const std::list<int> &lines);


    /**
     获取会话信息

     @param conversation 会话
     @return 会话信息
     */
    const ConversationInfo getConversationInfo(const Conversation &conversation);

    /**
     搜索会话

     @param keyword 关键词
     @param conversationTypes 会话类型
     @param lines 默认传 @[@(0)]
     @return 会话搜索结果信息
     */
    const std::list<ConversationSearchInfo> searchConversation(const std::string &keyword, const std::list<int> &conversationTypes, const std::list<int> &lines);

    /**
     删除会话

     @param conversation 会话
     @param clearMessage 是否删除会话中的消息
     */
    void removeConversation(const Conversation &conversation,bool clearMessage);

    /**
     设置或取消会话置顶

     @param conversation 会话
     @param top 是否置顶
     @param callback 结果回调
     */
    void setConversationTop(const Conversation &conversation, int top, GeneralVoidCallback *callback);

    /**
     设置会话免打扰

     @param conversation 会话
     @param silent 是否免打扰
     @param callback 结果回调
     */
    void setConversationSilent(const Conversation &conversation, bool silent, GeneralVoidCallback *callback);

    /**
     设置会话草稿

     @param conversation 会话
     @param draft 草稿
     */
    void setConversationDraft(const Conversation &conversation, const std::string &draft);

    /**
     获取指定类型会话的未读数

     @param conversationTypes 会话类型
     @param lines 默认传 @[@(0)]
     @return 未读数
     */
    UnreadCount getUnreadCount(const std::list<int> &conversationTypes, const std::list<int> &lines);

    /**
     获取某个会话的未读数

     @param conversation 会话
     @return 未读数
     */
    UnreadCount getUnreadCount(const Conversation &conversation);

    /**
     清空会话未读数

     @param conversation 会话
     */
    void clearUnreadStatus(const Conversation &conversation);

    /**
    清空会话类型的未读数

    @param conversationTypes 会话类型
    @param lines 默认传 @[@(0)]
    */
    void clearUnreadStatus(const std::list<int> &conversationTypes, const std::list<int> &lines);

    /**
     清空所有会话的未读数
     */
    void clearAllUnreadStatus();

    /**
     设置媒体消息已播放

     @param messageId 消息ID
     */
    void setMediaMessagePlayed(long messageId);

    /**
     获取消息
     @discuss 获取从fromIndex起count条旧的消息。如果想要获取比fromIndex新的消息，count传负值。

     @param conversation 会话
     @param contentTypes 消息类型
     @param fromIndex 起始index
     @param count 总数
     @return 消息实体
     */
    const std::list<Message> getMessages(const Conversation &conversation, const std::list<int> &contentTypes, int64_t fromIndex,int count, const std::string &user);

    /**
     获取某类会话信息

     @param conversationTypes 会话类型
     @param lines 默认传 @[@(0)]
     @param contentTypes 消息类型
     @param fromIndex 起始index
     @param count 总数
     @return 消息实体
     */
    const std::list<Message> getMessages(const std::list<int> &conversationTypes, const std::list<int> &lines, const std::list<int> &contentTypes, int64_t fromIndex, int count, const std::string &user);

    /**
     获取某类会话信息

     @param conversationTypes 会话类型
     @param lines 默认传 @[@(0)]
     @param messageStatuss 消息状态
     @param fromIndex 起始index
     @param count 总数
     @return 消息实体
     */
    const std::list<Message> getMessages(const std::list<int> &conversationTypes, const std::list<int> &lines, const std::list<MessageStatus> &messageStatuss, int64_t fromIndex, int count, const std::string &user);

    /**
     获取服务器消息

     @param conversation 会话
     @param beforeMessageUid 起始index
     @param count 总数
     @param callback 结果回调
     */
    void getRemoteMessages(const Conversation &conversation, const std::list<int> &contentTypes, int64_t beforeMessageUid, int count, GetRemoteMessageCallback *callback);
    /**
     获取消息

     @param messageId 消息ID
     @return 消息实体
     */
    const Message getMessage(long messageId);

    /**
     获取消息

     @param messageUid 消息UID
     @return 消息实体
     */
    const Message getMessageByUid(int64_t messageUid);

    /**
     搜索消息

     @param conversation 会话
     @param keyword 关键词
	 @param desc 顺序
     @param limit 数量
	 @param offset 便宜
	 @param withUser 对应用户
     @return 命中的消息
     */
    const std::list<Message> searchMessage(const Conversation &conversation, const std::string &keyword, bool desc, int limit, int offset, const std::string &withUser);

    /**
     发送消息

     @param conversation 会话
     @param content 消息内容
     @param toUsers 在会话中只发给该用户，如果为空则发到会话中
     @param expireDuration 消息的有效期，0不限期，单位秒
     @param callback 发送结果回调
     @return 消息实体
     */
    const Message sendMessage(const Conversation &conversation, const MessageContent &content, const std::list<std::string> &toUsers, int expireDuration, WFSendMessageCallback *callback);
    /**
     撤回消息

     @param messageUid 待撤回的消息Uid
     @param callback 结果的回调

     @discuss 服务器不检查可撤回时间，应用逻辑来处理。
     */
    void recallMessage(int64_t messageUid, GeneralVoidCallback *callback);

    /**
     上传媒体(图片、语音、文件等)

     @param fileName 文件名，可为空
     @param mediaData 媒体信息
     @param mediaType 媒体类型
     @param callback 回调
     */
    void uploadMedia(const std::string &fileName, const std::string mediaData, MediaType mediaType, UploadMediaCallback *callback);

    /**
     删除消息

     @param messageId 消息ID
     @return 是否删除成功
     */
    bool deleteMessage(long messageId);

    /**
     删除会话中的消息

     @param conversation 会话
     */
    void clearMessages(const Conversation &conversation);

    /**
     删除会话中的before之前的旧消息。

     @param conversation 会话，如果conversation为nil，则清除所有会话的消息。
     @param before 时间点，单位是毫秒
     */
    void clearMessages(const Conversation &conversation, int64_t before);

    /**
     插入消息

     @param conversation 会话
     @param content 消息内容
     @param status 消息状态，注意消息状态会影响消息方向
     @param serverTime 时间，0为当前时间
     @return 消息实体
     */
    const Message insert(const Conversation &conversation, const std::string &sender, const MessageContent &content, MessageStatus status, bool notify, int64_t serverTime);

    /**
     更新消息内容

     @param messageId 消息ID
     @param content 消息内容
     */
    void updateMessage(long messageId, const MessageContent &content);

    /**
     获取用户信息

     @param userId 用户ID
     @param refresh 是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。
     @return 本地的用户信息，可能为空
     */
    const UserInfo getUserInfo(const std::string &userId, bool refresh);

    /**
     获取用户信息
     @discussion 获取用户信息，如果在群中有群昵称也一并返回

     @param userId 用户ID
     @param groupId 群组ID
     @param refresh 是否强制从服务器更新，如果本地没有或者强制，会从服务器刷新，然后发出通知kUserInfoUpdated。
     @return 本地的用户信息，可能为空
     */
    const UserInfo getUserInfo(const std::string &userId, const std::string &groupId, bool refresh);

    /**
     批量获取用户信息

     @param userIds 用户ID列表
     @param groupId 群组ID
     @return 本地的用户信息列表。本地不存在的用户会返回只有id的用户信息，同时会拉取。
     */
    const std::list<UserInfo> getUserInfos(std::list<std::string> &userIds, const std::string &groupId);

    /**
     搜索用户

     @param keyword 关键词
     @param searchType 搜索类型
     @param page page
     @param callback 回调
     */
    void searchUser(const std::string &keyword, SearchUserType searchType, int page, SearchUserCallback *callback);

    /**
     查询用户和当前用户是否是好友关系

     @param userId 用户ID
     @return 是否是好友
     */
    bool isMyFriend(const std::string &userId);

    /**
     获取当前用户的好友列表

     @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
     @return 好友列表的用户ID
     */
    const std::list<std::string> getMyFriendList(bool refresh);


    /**
     搜索好友
     @param keyword 关键词
     @return 好友用户信息
     */
    const std::list<UserInfo> searchFriends(const std::string &keyword);

    /**
     搜索群组
     @param keyword 关键词
     @return 群组搜索结果
     */
    const std::list<GroupSearchInfo> searchGroups(const std::string &keyword);

    /**
     获取收到的好友请求

     @return 好友请求
     */
    const std::list<FriendRequest> getIncommingFriendRequest();

    /**
     获取发出的好友请求

     @return 好友请求
     */
    const std::list<FriendRequest> getOutgoingFriendRequest();

    /**
     从服务器更新好友请求
     */
    void loadFriendRequestFromRemote();

    /**
     获取未读的好友请求数

     @return 未读的好友请求数
     */
    int getUnreadFriendRequestStatus();

    /**
     清除好友请求的未读数
     */
    void clearUnreadFriendRequestStatus();

    /**
     删除好友

     @param userId 用户ID
     @param callback 回调
     */
    void deleteFriend(const std::string &userId, GeneralVoidCallback *callback);

    /**
     发送好友请求

     @param userId 用户ID
     @param reason 请求说明
     @param extra extra
	 @param callback 回调
     */
    void sendFriendRequest(const std::string &userId, const std::string &reason, const std::string &extra, GeneralVoidCallback *callback);

    /**
     处理好友请求

     @param userId 用户ID
     @param accpet 是否接受
	 @param friendExtra extra
     @param callback 回调
     */
    void handleFriendRequest(const std::string &userId, bool accpet, const std::string &friendExtra, GeneralVoidCallback *callback);

    /**
    获取用户的别名

    @param userId 用户ID
    */
    const std::string getFriendAlias(const std::string &userId);

    /**
    设置用户的别名

    @param userId 用户ID
    @param alias 别名
    @param callback 回调
    */
    void setFriend(const std::string &userId, const std::string &alias, GeneralVoidCallback *callback);

    /**
     查询用户是否被加入黑名单

     @param userId 用户ID
     @return 是否被加入黑名单
     */
    bool isBlackListed(const std::string &userId);

    /**
     获取当前用户的黑名单列表

     @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
     @return 黑名单列表的用户ID
     */
    const std::list<std::string> getBlackList(bool refresh);

    /**
     设置黑名单

     @param userId 用户ID
     @param isBlackListed YES 加入黑名单； NO 取消黑名单
     @param callback 回调
     */
    void setBlackList(const std::string &userId, bool isBlackListed, GeneralVoidCallback *callback);

    /**
     获取群成员信息

     @param groupId 群ID
     @param forceUpdate 是否强制从服务器更新，如果不刷新则从本地缓存中读取
     @return 群成员信息
     */
    const std::list<GroupMember> getGroupMembers(const std::string &groupId, bool forceUpdate);

    /**
     获取群信息

     @param groupId 群ID
     @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
     @return 群信息
     */
    const GroupInfo getGroupInfo(const std::string &groupId, bool refresh);

    /**
     获取群成员信息

     @param groupId 群ID
     @param memberId 群成员ID
     @return 群成员信息
     */
    const GroupMember getGroupMember(const std::string &groupId, const std::string &memberId);

    /**
     创建群

     @param groupId 群ID
     @param groupName 群名称
     @param groupPortrait 群头像
	 @param groupExtra 群Extra
     @param groupMembers 群成员
	 @param memberExtra 群成员Extra
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void createGroup(const std::string &groupId, const std::string &groupName, const std::string &groupPortrait, GroupType type, const std::string &groupExtra, const std::list<std::string> &groupMembers, const std::string &memberExtra, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralStringCallback *callback);

    /**
     添加群成员

     @param members 成员的用户ID列表
     @param groupId 群ID
	 @param memberExtra 成员的Extra
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void addMembers(const std::list<std::string> &members, const std::string &groupId, const std::string &memberExtra, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     踢出群成员

     @param members 成员的用户ID列表
     @param groupId 群ID
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void kickoffMembers(const std::list<std::string> &members, const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     退群

     @param groupId 群ID
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void quitGroup(const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     解散群

     @param groupId 群ID
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void dismissGroup(const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     修改群信息

     @param groupId 群ID
     @param type    要修改的群属性
     @param newValue    要修改的群属性值
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void modifyGroupInfo(const std::string &groupId, ModifyGroupInfoType type, const std::string &newValue, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     修改群昵称

     @param groupId 群ID
     @param newAlias 昵称
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void modifyGroupAlias(const std::string &groupId, const std::string &newAlias, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     转移群主

     @param groupId 群ID
     @param newOwner 群主的用户ID
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void transferGroup(const std::string &groupId, const std::string &newOwner, const std::list<int> &notifyLines, const MessageContent &notifyContent,  GeneralVoidCallback *callback);

    /**
     设置群管理

     @param groupId 群ID
     @param isSet    设置或取消
     @param memberId    成员ID
     @param notifyLines 默认传 @[@(0)]
     @param notifyContent 通知消息
     @param callback 回调
     */
    void setGroupManager(const std::string &groupId, bool isSet, const std::list<std::string> &memberId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback);

    /**
     获取当前用户收藏的群组

     @return 当前用户收藏的群组ID
     */
    const std::list<std::string> getFavGroups();

    /**
     是否是当前用户收藏的群组

     @return 是否是当前用户收藏的群组
     */
    bool isFavGroup(const std::string &groupId);

    /**
     设置群组收藏状态

     @param groupId 群组ID
     @param fav 是否收藏
     @param callback 回调
     */
    void setFavGroup(const std::string &groupId, bool fav, GeneralVoidCallback *callback);

    /**
     获取个人设置

     @param scope 设置项的scope
     @param key 设置项的key
     @return 设置值
     */
    const std::string getUserSetting(UserSettingScope scope, const std::string &key);

    /**
     获取个人一类设置

     @param scope 设置项的scope
     @return scope对应的所有设置值
     */
    const std::map<std::string, std::string>getUserSettings(UserSettingScope scope);

    /**
     设置个人设置项

     @param scope 设置项的scope
     @param key 设置项的key
     @param value 值
     @param callback 成功的回调
     */
    void setUserSetting(UserSettingScope scope, const std::string &key, const std::string &value, GeneralVoidCallback *callback);

    /**
     修改个人信息

     @param values 信息
     @param callback 成功的回调

     @discuss 性别属性是int类型，修改时需要转为字符串类型
     */
    void modifyMyInfo(const std::list<std::pair<int, std::string> > &values, GeneralVoidCallback *callback);

    /**
     是否是全局禁止通知
    */
    bool isGlobalSilent();

    /**
     设置全局禁止通知

     @param slient 是否禁止通知
     @param callback 回调
     */
    void setGlobalSilent(bool slient, GeneralVoidCallback *callback);

    /**
    通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”
    */
    bool isHiddenNotificationDetail();

    /**
    设置通知是否隐藏详情，隐藏详情时通知内容为“您有一条新消息”

    @param hidden 是否隐藏详情
    @param callback 回调
    */
    void setHiddenNotificationDetail(bool hidden, GeneralVoidCallback *callback);

    /**
    群聊中是否显示群成员名称

    @param hidden 是否显示
    @param groupId 群组ID
    @param callback 回调
    */
    void setHiddenGroupMemberName(bool hidden, const std::string &groupId, GeneralVoidCallback *callback);


    /**
    加入聊天室

    @param chatroomId 聊天室ID
    @param callback 回调
    */
    void joinChatroom(const std::string &chatroomId, GeneralVoidCallback *callback);

    /**
    退出聊天室

    @param chatroomId 聊天室ID
    @param callback 回调
    */
    void quitChatroom(const std::string &chatroomId, GeneralVoidCallback *callback);

    /**
    获取聊天室信息

    @param chatroomId 聊天室ID
    @param updateDt 上次聊天室获取时间戳，可以为0
    @param callback 回调
    */
    void getChatroomInfo(const std::string &chatroomId, int64_t updateDt, GetChatroomInfoCallback *callback);

    /**
    获取聊天室成员信息

    @param chatroomId 聊天室ID
    @param maxCount 最大成员数量，建议不超过100
    @param callback 回调
    */
    void getChatroomMemberInfo(const std::string &chatroomId, int maxCount, GetChatroomMemberInfoCallback *callback);

    /**
     创建频道

     @param channelName 频道名称
     @param channelPortrait 频道头像
     @param desc 频道描述
     @param extra 频道extra
     @param callback 回调
     */
    void createChannel(const std::string &channelName, const std::string &channelPortrait, const std::string &desc, const std::string &extra, GetChannelInfoCallback *callback);

    /**
     获取频道信息

     @param channelId 频道ID
     @param refresh 是否强制从服务器更新，如果不刷新则从本地缓存中读取
     @return 群信息
     */
    ChannelInfo getChannelInfo(const std::string &channelId, bool refresh);

    /**
     修改频道信息

     @param channelId 群ID
     @param type    要修改的群属性
     @param newValue    要修改的群属性值
     @param callback 回调
     */
    void modifyChannelInfo(const std::string &channelId, ModifyChannelInfoType type, const std::string &newValue, GeneralVoidCallback *callback);

    /**
     搜索频道

     @param keyword 关键词
     @param callback 回调
     */
    void searchChannel(const std::string &keyword, SearchChannelCallback *callback);

    /**
     是否收听频道

     @param channelId 频道ID
     @return YES，收听；NO，未收听
     */
    bool isListenedChannel(const std::string &channelId);

    /**
     收听或者取消收听频道

     @param channelId 频道ID
     @param listen 是否收听
     @param callback 回调
     */
    void listenChannel(const std::string &channelId, bool listen, GeneralVoidCallback *callback);

    /**
     获取当前用户创建的频道

     @return 当前用户创建的频道ID
     */
    const std::list<std::string> getMyChannels();

    /**
     获取当前用户收听的频道

     @return 当前用户收听的频道ID
     */
    const std::list<std::string> getListenedChannels();

    /**
     销毁频道

     @param channelId 频道ID
     @param callback 回调
     */
    void destoryChannel(const std::string &channelId, GeneralVoidCallback *callback);

	 void getAuthorizedMediaUrl(long long messageId, int mediaType, const std::string & mediaPath, GeneralStringCallback * callback);



    /**
     payload转为content，一般客户不需要使用
     */
    MessageContent *getContent(const MessagePayload &payload);
public:
    virtual ~ChatClient();
private:
    ChatClient();
    std::map<int, const MessageContentPrototype *> messageContentFactorys;
    const std::string convertDllString(const std::string *pDllString);
};
};
