//
//  WFClient.h
//  IMClient
//
//  Created by Heavyrain.Lee on 2020/1/7.
//  Copyright © 2020 Wildfirechat. All rights reserved.
//

#ifndef WFClient_h
#define WFClient_h

#ifdef WIN32
#ifdef PROTOWRAPPER_EXPORTS
#define PROTOWRAPPER_API __declspec(dllexport)
#else
#define PROTOWRAPPER_API __declspec(dllimport)
#endif
#else
#define PROTOWRAPPER_API
#endif


#include <string>
#include <list>


extern PROTOWRAPPER_API void HelloWorld(char* name);

namespace WFClient {

	extern PROTOWRAPPER_API void releaseDllString(const std::string *dllString);
/*
 * 说明：1000以下为系统保留类型，自定义消息请使用1000以上数值。
 * 系统消息类型中100以下为常用基本类型消息。100-199位群组消息类型。400-499为VoIP消息类型.
 */
////基本消息类型
////未知类型的消息
//#define MESSAGE_CONTENT_TYPE_UNKNOWN 0
////文本消息
//#define MESSAGE_CONTENT_TYPE_TEXT 1
////语音消息
//#define MESSAGE_CONTENT_TYPE_SOUND 2
////图片消息
//#define MESSAGE_CONTENT_TYPE_IMAGE 3
////位置消息
//#define MESSAGE_CONTENT_TYPE_LOCATION 4
////文件消息
//#define MESSAGE_CONTENT_TYPE_FILE 5
////视频消息
//#define MESSAGE_CONTENT_TYPE_VIDEO 6
////动态表情消息
//#define MESSAGE_CONTENT_TYPE_STICKER 7
////图文消息
//#define MESSAGE_CONTENT_TYPE_IMAGETEXT 8
////存储不计数文本消息
//#define MESSAGE_CONTENT_TYPE_P_TEXT 9
//
//
////撤回消息
//#define MESSAGE_CONTENT_TYPE_RECALL 80
//
////提醒消息
//#define MESSAGE_CONTENT_TYPE_TIP 90
//
////正在输入消息
//#define MESSAGE_CONTENT_TYPE_TYPING 91
//
////通知消息类型
////创建群的通知消息
//#define MESSAGE_CONTENT_TYPE_CREATE_GROUP 104
////加群的通知消息
//#define MESSAGE_CONTENT_TYPE_ADD_GROUP_MEMBER 105
////踢出群成员的通知消息
//#define MESSAGE_CONTENT_TYPE_KICKOF_GROUP_MEMBER 106
////退群的通知消息
//#define MESSAGE_CONTENT_TYPE_QUIT_GROUP 107
////解散群的通知消息
//#define MESSAGE_CONTENT_TYPE_DISMISS_GROUP 108
////转让群主的通知消息
//#define MESSAGE_CONTENT_TYPE_TRANSFER_GROUP_OWNER 109
////修改群名称的通知消息
//#define MESSAGE_CONTENT_TYPE_CHANGE_GROUP_NAME 110
////修改群昵称的通知消息
//#define MESSAGE_CONTENT_TYPE_MODIFY_GROUP_ALIAS 111
////修改群头像的通知消息
//#define MESSAGE_CONTENT_TYPE_CHANGE_GROUP_PORTRAIT 112
//
//#define MESSAGE_CONTENT_TYPE_CHANGE_MUTE 113
//#define MESSAGE_CONTENT_TYPE_CHANGE_JOINTYPE 114
//#define MESSAGE_CONTENT_TYPE_CHANGE_PRIVATECHAT 115
//#define MESSAGE_CONTENT_TYPE_CHANGE_SEARCHABLE 116
//#define MESSAGE_CONTENT_TYPE_SET_MANAGER 117
//
////VoIP开始消息
//#define VOIP_CONTENT_TYPE_START 400
////VoIP结束消息
//#define VOIP_CONTENT_TYPE_END 402
//
//#define VOIP_CONTENT_TYPE_ACCEPT 401
//#define VOIP_CONTENT_TYPE_SIGNAL 403
//#define VOIP_CONTENT_TYPE_MODIFY 404
//#define VOIP_CONTENT_TYPE_ACCEPT_T 405


//Global callback
typedef void (*fun_connection_callback)(int);
typedef void (*fun_receive_message_callback)(const std::string &messages, bool moreMsg);
typedef void (*fun_recall_message_callback)(const std::string &operatorId, int64_t messageUid);
typedef void (*fun_delete_message_callback)(int64_t messageUid);
typedef void (*fun_message_receipt_callback)(const std::string &strReceipt);

typedef void (*fun_userInfo_update_callback)(const std::string &userInfos);

typedef void (*fun_groupInfo_update_callback)(const std::string &groupInfos);

typedef void (*fun_groupMembers_update_callback)(const std::string &groupId);

typedef void (*fun_friendList_update_callback)(const std::string &friendList);

typedef void (*fun_receive_friendRequest_callback)(const std::string &newRequests);

typedef void (*fun_user_setting_update_callback)();

typedef void (*fun_channelInfo_update_callback)(const std::string &channelInfo);


//function call back
typedef void (*fun_general_void_success_callback)(void *pObjectect);

typedef void (*fun_general_void_error_callback)(void *pObjectect, int errorCode);

typedef void (*fun_general_string_success_callback)(void *pObjectect, const std::string &val);

typedef void (*fun_general_string_error_callback)(void *pObjectect, int errorCode);


extern PROTOWRAPPER_API bool connect(const std::string &userId, const std::string &token);

extern PROTOWRAPPER_API void disconnect(int flag);

extern PROTOWRAPPER_API void setConnectionStatusListener(fun_connection_callback callback);

extern PROTOWRAPPER_API void setReceiveMessageListener(fun_receive_message_callback receiveCallback, fun_recall_message_callback recallCallback, fun_delete_message_callback deleteCallback, fun_message_receipt_callback deliveryCallback, fun_message_receipt_callback readedCallback);

extern PROTOWRAPPER_API void setUserInfoUpdateListener(fun_userInfo_update_callback callback);

extern PROTOWRAPPER_API void setGroupInfoUpdateListener(fun_groupInfo_update_callback callback);

extern PROTOWRAPPER_API void setGroupMemberUpdateListener(fun_groupMembers_update_callback callback);

extern PROTOWRAPPER_API void setFriendUpdateListener(fun_friendList_update_callback callback);

extern PROTOWRAPPER_API void setFriendRequestListener(fun_receive_friendRequest_callback callback);

extern PROTOWRAPPER_API void setSettingUpdateListener(fun_user_setting_update_callback callback);
extern PROTOWRAPPER_API void setChannelInfoUpdateListener(fun_channelInfo_update_callback callback);

extern PROTOWRAPPER_API bool isLogin();

extern PROTOWRAPPER_API int getConnectionStatus();

extern PROTOWRAPPER_API const std::string* getClientId();

extern PROTOWRAPPER_API int64_t getServerDeltaTime();

extern PROTOWRAPPER_API const std::string* getCurrentUserId();

extern PROTOWRAPPER_API const std::string* getConversationInfos(std::list<int> types, std::list<int> ls);

extern PROTOWRAPPER_API void registerMessageFlag(int type, int flag);

extern PROTOWRAPPER_API const std::string* getConversationInfo(int conversationType, const std::string &target, int line);

extern PROTOWRAPPER_API const std::string* searchConversation(std::list<int> types, std::list<int> ls, const std::string &keyword);

extern PROTOWRAPPER_API void removeConversation(int conversationType, const std::string &target, int line, bool clearMsg);

extern PROTOWRAPPER_API void setConversationTop(int conversationType, const std::string &target, int line, bool isTop, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern PROTOWRAPPER_API void setConversationSlient(int conversationType, const std::string &target, int line, bool isSlient, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern PROTOWRAPPER_API void setConversationDraft(int conversationType, const std::string &target, int line, const std::string &draft);

extern PROTOWRAPPER_API const std::string* getUnreadCount(std::list<int> types, std::list<int> ls);

extern PROTOWRAPPER_API const std::string* getConversationUnreadCount(int conversationType, const std::string &target, int line);

extern PROTOWRAPPER_API void clearUnreadStatus(int conversationType, const std::string &target, int line);

extern PROTOWRAPPER_API void clearUnreadStatus(const std::list<int> &types, const std::list<int> &lines);

extern PROTOWRAPPER_API void clearAllUnreadStatus();

extern PROTOWRAPPER_API void setMediaMessagePlayed(long messageId);

extern PROTOWRAPPER_API const std::string* getMessages(int conversationType, const std::string &target, int line, std::list<int> contTypes, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern PROTOWRAPPER_API const std::string* getMessages(const std::list<int> &conversationTypes, const std::list<int> &lines, std::list<int> contTypes, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern PROTOWRAPPER_API const std::string* getMessagesByMessageStatus(const std::list<int> &conversationTypes, const std::list<int> &lines, const std::list<int> &messageStatuses, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern PROTOWRAPPER_API void getRemoteMessages(int conversationType, const std::string &target, int line, const std::list<int> &contentTypes, int64_t beforeUid, int count, fun_general_string_success_callback successCallback, fun_general_void_error_callback errorCallback, void *pObjectect);

extern PROTOWRAPPER_API const std::string* getMessage(long messageId);

extern PROTOWRAPPER_API const std::string* getMessageByUid(int64_t messageUid);


extern PROTOWRAPPER_API const std::string* searchMessage(int conversationType, const std::string &target, int line, const std::string &keyword, int count);

typedef void (*fun_sendMessage_success_callback)(void *pObjectect, int64_t messageUid, int64_t timestamp);

typedef void (*fun_sendMessage_progress_callback)(void *pObjectect, int uploaded, int total);

typedef void (*fun_sendMessage_error_callback)(void *pObjectect, int errorCode);


extern PROTOWRAPPER_API const std::string* sendMessage(int conversationType, const std::string &target, int line, const std::string &strcont, const std::list<std::string> &toUsers, int expireDuration, fun_sendMessage_success_callback successCallback, fun_sendMessage_error_callback errorCallback,  fun_sendMessage_progress_callback progressCallback, void *pObjectect);

extern PROTOWRAPPER_API void recallMessage(int64_t messageUid, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern PROTOWRAPPER_API void uploadMedia(const std::string &strName, const char* data, int dataLen, int mediaType, fun_general_string_success_callback successCB, fun_general_void_error_callback errorCB, fun_sendMessage_progress_callback progressCB, void *pObject);

extern PROTOWRAPPER_API bool deleteMessage(long messageId);

extern PROTOWRAPPER_API void clearMessages(int conversationType, const std::string &target, int line);

extern PROTOWRAPPER_API void clearMessages(int conversationType, const std::string &target, int line, int64_t before);

extern PROTOWRAPPER_API const std::string* insertMessage(int conversationType, const std::string &target, int line, const std::string &strfrom, const std::string &strcont, int status, bool notify, int64_t serverTime);

extern PROTOWRAPPER_API void updateMessage(long messageId, const std::string &strcont);

extern PROTOWRAPPER_API const std::string* getConversationRead(int conversationType, const std::string &target, int line);
extern PROTOWRAPPER_API const std::string* getMessageDelivery(int conversationType, const std::string &target);

extern PROTOWRAPPER_API const std::string* getUserInfo(const std::string &userId, bool refresh, const std::string &groupId);

extern PROTOWRAPPER_API const std::string* getUserInfos(const std::list<std::string> &userIds, const std::string &groupId);

extern PROTOWRAPPER_API void searchUser(const std::string &keyword, int searchType, int page, fun_general_string_success_callback successCB, fun_general_string_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API bool isMyFriend(const std::string &userId);

extern PROTOWRAPPER_API const std::string* getMyFriendList(bool refresh);

extern PROTOWRAPPER_API const std::string* searchFriends(const std::string &keyword);

extern PROTOWRAPPER_API const std::string* searchGroups(const std::string &keyword);

extern PROTOWRAPPER_API const std::string* getIncommingFriendRequest();

extern PROTOWRAPPER_API const std::string* getOutgoingFriendRequest();

extern PROTOWRAPPER_API const std::string* getFriendRequest(const std::string &userId, bool incomming);

extern PROTOWRAPPER_API void loadFriendRequestFromRemote();

extern PROTOWRAPPER_API int getUnreadFriendRequestStatus();

extern PROTOWRAPPER_API void clearUnreadFriendRequestStatus();

extern PROTOWRAPPER_API void deleteFriend(const std::string &userId, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API const std::string* getFriendAlias(const std::string &userId);

extern PROTOWRAPPER_API void setFriendAlias(const std::string &userId, const std::string &alias, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API const std::string* getFriendExtra(const std::string &userId);

extern PROTOWRAPPER_API void sendFriendRequest(const std::string &userId, const std::string &reason, const std::string &extra, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API void handleFriendRequest(const std::string &userId, bool accept, const std::string &extra, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API bool isBlackListed(const std::string &userId);

extern PROTOWRAPPER_API const std::string* getBlackList(bool refresh);

extern PROTOWRAPPER_API void setBlackList(const std::string &userId, bool isBlackListed, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);
extern PROTOWRAPPER_API const std::string* getGroupMembers(const std::string &groupId, bool refresh);

extern PROTOWRAPPER_API const std::string* getGroupInfo(const std::string &groupId, bool refresh);

extern PROTOWRAPPER_API const std::string* getGroupMember(const std::string &groupId, const std::string &memberId);

extern PROTOWRAPPER_API void createGroup(const std::string &groupId, int groupType, const std::string &groupName, const std::string &groupPortrait, const std::string &groupExtra, const std::list<std::string> &members, const std::string &memberExtra, const std::list<int> &lines, const std::string &strCont, fun_general_string_success_callback successCB, fun_general_string_error_callback errorCB, void *pObject);

extern PROTOWRAPPER_API void addMembers(const std::string &groupId, const std::list<std::string> &members, const std::string &memberExtra, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void kickoffMembers(const std::string &groupId, const std::list<std::string> &members, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void quitGroup(const std::string &groupId, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void dismissGroup(const std::string &groupId, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void modifyGroupInfo(const std::string &groupId, int type, const std::string &newValue, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void modifyGroupAlias(const std::string &groupId, const std::string &newAlias, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void transferGroup(const std::string &groupId, const std::string &newOwner, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);


extern PROTOWRAPPER_API void setGroupManager(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);
extern PROTOWRAPPER_API void muteGroupMember(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);
extern PROTOWRAPPER_API void allowGroupMember(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API const std::string* getFavGroups();
extern PROTOWRAPPER_API const std::string* getUserSetting(int scope, const std::string &key);

extern PROTOWRAPPER_API const std::string* getUserSettings(int scope);

extern PROTOWRAPPER_API void setUserSetting(int scope, const std::string &key, const std::string &value, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);


extern PROTOWRAPPER_API bool isFavGroup(const std::string &groupId);

extern PROTOWRAPPER_API void setFavGroup(const std::string &groupId, bool fav, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API const std::string* getFavUsers();
extern PROTOWRAPPER_API bool isFavUser(const std::string &userId);
extern PROTOWRAPPER_API void setFavUser(const std::string &userId, bool fav, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObj);

extern PROTOWRAPPER_API void modifyMyInfo(const std::list<std::pair<int, std::string> > &infos, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API bool isGlobalSlient();
extern PROTOWRAPPER_API void setGlobalSlient(bool slient, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API bool isHiddenNotificationDetail();

extern PROTOWRAPPER_API void setHiddenNotificationDetail(bool hidden, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API bool isHiddenGroupMemberName(const std::string &groupId);

extern PROTOWRAPPER_API void setHiddenGroupMemberName(const std::string &groupId, bool hidden, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void joinChatroom(const std::string &chatroomId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void quitChatroom(const std::string &chatroomId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void getChatroomInfo(const std::string &chatroomId, int64_t updateDt, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void getChatroomMemberInfo(const std::string &chatroomId, int maxCount, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void createChannel(const std::string &channelName, const std::string &channelPortrait, int status, const std::string &desc, const std::string &extra, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API const std::string* getChannelInfo(const std::string &channelId, bool refresh);

extern PROTOWRAPPER_API void modifyChannelInfo(const std::string &channelId, int type, const std::string &newValue, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API void searchChannel(const std::string &keyword, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API bool isListenedChannel(const std::string &channelId);

extern PROTOWRAPPER_API void listenChannel(const std::string &channelId, bool listen, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API const std::string* getMyChannels();

extern PROTOWRAPPER_API const std::string* getListenedChannels();

extern PROTOWRAPPER_API void destoryChannel(const std::string &channelId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern PROTOWRAPPER_API const std::string* getAppPath();

extern PROTOWRAPPER_API void getAuthorizedMediaUrl(long long messageUid, int mediaType, const std::string &mediaPath, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObj);

}

#endif /* WFClient_h */
