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

#define WFCAPI __stdcall
#else
#define PROTOWRAPPER_API
#define WFCAPI
#endif


#include <string>
#include <list>

namespace WFClient {

	extern "C" PROTOWRAPPER_API void WFCAPI releaseDllString(const std::string *dllString);
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
typedef void (__stdcall *fun_connection_callback)(int);
typedef void (__stdcall *fun_receive_message_callback)(const std::string &messages, bool moreMsg);
typedef void (__stdcall *fun_recall_message_callback)(const std::string &operatorId, int64_t messageUid);
typedef void (__stdcall *fun_delete_message_callback)(int64_t messageUid);
typedef void (__stdcall *fun_message_receipt_callback)(const std::string &strReceipt);

typedef void (__stdcall *fun_userInfo_update_callback)(const std::string &userInfos);

typedef void (__stdcall *fun_groupInfo_update_callback)(const std::string &groupInfos);

typedef void (__stdcall *fun_groupMembers_update_callback)(const std::string &groupId);

typedef void (__stdcall *fun_friendList_update_callback)(const std::string &friendList);

typedef void (__stdcall *fun_receive_friendRequest_callback)(const std::string &newRequests);

typedef void (__stdcall *fun_user_setting_update_callback)();

typedef void (__stdcall *fun_channelInfo_update_callback)(const std::string &channelInfo);


//function call back
typedef void (__stdcall *fun_general_void_success_callback)(void *pObjectect);

typedef void (__stdcall *fun_general_void_error_callback)(void *pObjectect, int errorCode);

typedef void (__stdcall *fun_general_string_success_callback)(void *pObjectect, const std::string &val);

typedef void (__stdcall *fun_general_string_error_callback)(void *pObjectect, int errorCode);


extern "C" PROTOWRAPPER_API int64_t WFCAPI connect2Server(const std::string &userId, const std::string &token);

extern "C" PROTOWRAPPER_API void WFCAPI setDBPath(const std::string &path);

extern "C" PROTOWRAPPER_API void WFCAPI disconnect(int flag);

extern "C" PROTOWRAPPER_API void WFCAPI setConnectionStatusListener(fun_connection_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setReceiveMessageListener(fun_receive_message_callback receiveCallback, fun_recall_message_callback recallCallback, fun_delete_message_callback deleteCallback, fun_message_receipt_callback deliveryCallback, fun_message_receipt_callback readedCallback);

extern "C" PROTOWRAPPER_API void WFCAPI setUserInfoUpdateListener(fun_userInfo_update_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setGroupInfoUpdateListener(fun_groupInfo_update_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setGroupMemberUpdateListener(fun_groupMembers_update_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setFriendUpdateListener(fun_friendList_update_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setFriendRequestListener(fun_receive_friendRequest_callback callback);

extern "C" PROTOWRAPPER_API void WFCAPI setSettingUpdateListener(fun_user_setting_update_callback callback);
extern "C" PROTOWRAPPER_API void WFCAPI setChannelInfoUpdateListener(fun_channelInfo_update_callback callback);

extern "C" PROTOWRAPPER_API bool WFCAPI isLogin();

extern "C" PROTOWRAPPER_API int WFCAPI WFCAPI getConnectionStatus();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getClientId();

extern "C" PROTOWRAPPER_API int64_t WFCAPI getServerDeltaTime();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getCurrentUserId();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getConversationInfos(std::list<int> types, std::list<int> ls);

extern "C" PROTOWRAPPER_API void WFCAPI registerMessageFlag(int type, int flag);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getConversationInfo(int conversationType, const std::string &target, int line);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI searchConversation(std::list<int> types, std::list<int> ls, const std::string &keyword);

extern "C" PROTOWRAPPER_API void WFCAPI removeConversation(int conversationType, const std::string &target, int line, bool clearMsg);

extern "C" PROTOWRAPPER_API void WFCAPI setConversationTop(int conversationType, const std::string &target, int line, int isTop, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI setConversationSlient(int conversationType, const std::string &target, int line, bool isSlient, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI setConversationDraft(int conversationType, const std::string &target, int line, const std::string &draft);

extern "C" PROTOWRAPPER_API void WFCAPI setConversationTimestamp(int conversationType, const std::string &target, int line, int64_t timestamp);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getUnreadCount(std::list<int> types, std::list<int> ls);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getConversationUnreadCount(int conversationType, const std::string &target, int line);

extern "C" PROTOWRAPPER_API void WFCAPI clearUnreadStatus(int conversationType, const std::string &target, int line);

extern "C" PROTOWRAPPER_API void WFCAPI clearUnreadStatusEx(const std::list<int> &types, const std::list<int> &lines);

extern "C" PROTOWRAPPER_API void WFCAPI clearAllUnreadStatus();

extern "C" PROTOWRAPPER_API void WFCAPI setMediaMessagePlayed(long messageId);

extern "C" PROTOWRAPPER_API bool WFCAPI setMessageLocalExtra(long messageId, const std::string &localExtra);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessages(int conversationType, const std::string &target, int line, std::list<int> contTypes, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessagesEx(const std::list<int> &conversationTypes, const std::list<int> &lines, std::list<int> contTypes, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessagesByMessageStatus(const std::list<int> &conversationTypes, const std::list<int> &lines, const std::list<int> &messageStatuses, int64_t fromIndex, bool direction, int count, const std::string &withUser);

extern "C" PROTOWRAPPER_API void WFCAPI getRemoteMessages(int conversationType, const std::string &target, int line, const std::list<int> &contentTypes, int64_t beforeUid, int count, fun_general_string_success_callback successCallback, fun_general_void_error_callback errorCallback, void *pObjectect);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessage(long messageId);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessageByUid(int64_t messageUid);

extern "C" PROTOWRAPPER_API long WFCAPI getFirstUnreadMessageId(int conversationType, const std::string &target, int line);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI searchMessage(int conversationType, const std::string &target, int line, const std::string &keyword, bool desc, int limit, int offset, const std::string &withUser);

typedef void (__stdcall *fun_sendMessage_success_callback)(void *pObjectect, int64_t messageUid, int64_t timestamp);

typedef void (__stdcall *fun_sendMessage_prepared_callback)(void *pObjectect, int messageId, int64_t saveTime);

typedef void (__stdcall *fun_sendMessage_progress_callback)(void *pObjectect, int uploaded, int total);

typedef void(__stdcall *fun_sendMessage_media_uploaded_callback)(void *pObjectect, const std::string &remoteUrl);

typedef void (__stdcall *fun_sendMessage_error_callback)(void *pObjectect, int errorCode);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI sendMessage(int conversationType, const std::string &target, int line, const std::string &strcont, const std::list<std::string> &toUsers, int expireDuration, fun_sendMessage_success_callback successCallback, fun_sendMessage_error_callback errorCallback, fun_sendMessage_prepared_callback preparedCallback, fun_sendMessage_progress_callback progressCallback, fun_sendMessage_media_uploaded_callback uploadedCallback, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI recallMessage(int64_t messageUid, fun_general_void_success_callback succCallback, fun_general_void_error_callback errCallback, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI uploadMedia(const std::string &strName, const char* data, int dataLen, int mediaType, fun_general_string_success_callback successCB, fun_general_void_error_callback errorCB, fun_sendMessage_progress_callback progressCB, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI deleteMessage(long messageId);

extern "C" PROTOWRAPPER_API void WFCAPI clearMessages(int conversationType, const std::string &target, int line);

extern "C" PROTOWRAPPER_API void WFCAPI clearMessagesBefore(int conversationType, const std::string &target, int line, int64_t before);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI insertMessage(int conversationType, const std::string &target, int line, const std::string &strfrom, const std::string &strcont, int status, bool notify, int64_t serverTime);

extern "C" PROTOWRAPPER_API void WFCAPI updateMessage(long messageId, const std::string &strcont);
extern "C" PROTOWRAPPER_API void WFCAPI updateMessageContentAndTime(long messageId, const std::string &strcont, int64_t timestamp);
extern "C" PROTOWRAPPER_API void WFCAPI updateMessageStatus(long messageId, int messageStatus);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getConversationRead(int conversationType, const std::string &target, int line);
extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMessageDelivery(int conversationType, const std::string &target);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getUserInfo(const std::string &userId, bool refresh, const std::string &groupId);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getUserInfos(const std::list<std::string> &userIds, const std::string &groupId);

extern "C" PROTOWRAPPER_API void WFCAPI searchUser(const std::string &keyword, int searchType, int page, fun_general_string_success_callback successCB, fun_general_string_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isMyFriend(const std::string &userId);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMyFriendList(bool refresh);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI searchFriends(const std::string &keyword);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI searchGroups(const std::string &keyword);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getIncommingFriendRequest();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getOutgoingFriendRequest();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getFriendRequest(const std::string &userId, bool incomming);

extern "C" PROTOWRAPPER_API void WFCAPI loadFriendRequestFromRemote();

extern "C" PROTOWRAPPER_API int WFCAPI getUnreadFriendRequestStatus();

extern "C" PROTOWRAPPER_API void WFCAPI clearUnreadFriendRequestStatus();

extern "C" PROTOWRAPPER_API void WFCAPI deleteFriend(const std::string &userId, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getFriendAlias(const std::string &userId);

extern "C" PROTOWRAPPER_API void WFCAPI setFriendAlias(const std::string &userId, const std::string &alias, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getFriendExtra(const std::string &userId);

extern "C" PROTOWRAPPER_API void WFCAPI sendFriendRequest(const std::string &userId, const std::string &reason, const std::string &extra, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI handleFriendRequest(const std::string &userId, bool accept, const std::string &extra, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isBlackListed(const std::string &userId);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getBlackList(bool refresh);

extern "C" PROTOWRAPPER_API void WFCAPI setBlackList(const std::string &userId, bool isBlackListed, fun_general_void_success_callback successCB, fun_general_void_error_callback errorCB, void *pObject);
extern "C" PROTOWRAPPER_API const std::string* WFCAPI getGroupMembers(const std::string &groupId, bool refresh);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getGroupInfo(const std::string &groupId, bool refresh);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getGroupMember(const std::string &groupId, const std::string &memberId);

extern "C" PROTOWRAPPER_API void WFCAPI createGroup(const std::string &groupId, int groupType, const std::string &groupName, const std::string &groupPortrait, const std::string &groupExtra, const std::list<std::string> &members, const std::string &memberExtra, const std::list<int> &lines, const std::string &strCont, fun_general_string_success_callback successCB, fun_general_string_error_callback errorCB, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI addMembers(const std::string &groupId, const std::list<std::string> &members, const std::string &memberExtra, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI kickoffMembers(const std::string &groupId, const std::list<std::string> &members, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI quitGroup(const std::string &groupId, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI dismissGroup(const std::string &groupId, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI modifyGroupInfo(const std::string &groupId, int type, const std::string &newValue, std::list<int> lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI modifyGroupAlias(const std::string &groupId, const std::string &newAlias, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI modifyGroupMemberAlias(const std::string &groupId, const std::string &memberId, const std::string &newAlias, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI modifyGroupMemberExtra(const std::string &groupId, const std::string &memberId, const std::string &newExtra, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI transferGroup(const std::string &groupId, const std::string &newOwner, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);


extern "C" PROTOWRAPPER_API void WFCAPI setGroupManager(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);
extern "C" PROTOWRAPPER_API void WFCAPI muteGroupMember(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);
extern "C" PROTOWRAPPER_API void WFCAPI allowGroupMember(const std::string &groupId, bool isSet, const std::list<std::string> &members, const std::list<int> &lines, const std::string &strCont, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getFavGroups();
extern "C" PROTOWRAPPER_API const std::string* WFCAPI getUserSetting(int scope, const std::string &key);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getUserSettings(int scope);

extern "C" PROTOWRAPPER_API void WFCAPI setUserSetting(int scope, const std::string &key, const std::string &value, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);


extern "C" PROTOWRAPPER_API bool WFCAPI isFavGroup(const std::string &groupId);

extern "C" PROTOWRAPPER_API void WFCAPI setFavGroup(const std::string &groupId, bool fav, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getFavUsers();
extern "C" PROTOWRAPPER_API bool WFCAPI isFavUser(const std::string &userId);
extern "C" PROTOWRAPPER_API void WFCAPI setFavUser(const std::string &userId, bool fav, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObj);

extern "C" PROTOWRAPPER_API void WFCAPI modifyMyInfo(const std::list<std::pair<int, std::string> > &infos, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isGlobalSilent();
extern "C" PROTOWRAPPER_API void WFCAPI setGlobalSilent(bool slient, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isHiddenNotificationDetail();

extern "C" PROTOWRAPPER_API void WFCAPI setHiddenNotificationDetail(bool hidden, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isHiddenGroupMemberName(const std::string &groupId);

extern "C" PROTOWRAPPER_API void WFCAPI setHiddenGroupMemberName(const std::string &groupId, bool hidden, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI joinChatroom(const std::string &chatroomId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI quitChatroom(const std::string &chatroomId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI getChatroomInfo(const std::string &chatroomId, int64_t updateDt, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI getChatroomMemberInfo(const std::string &chatroomId, int maxCount, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI createChannel(const std::string &channelName, const std::string &channelPortrait, const std::string &desc, const std::string &extra, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getChannelInfo(const std::string &channelId, bool refresh);

extern "C" PROTOWRAPPER_API void WFCAPI modifyChannelInfo(const std::string &channelId, int type, const std::string &newValue, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API void WFCAPI searchChannel(const std::string &keyword, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API bool WFCAPI isListenedChannel(const std::string &channelId);

extern "C" PROTOWRAPPER_API void WFCAPI listenChannel(const std::string &channelId, bool listen, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getMyChannels();

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getListenedChannels();

extern "C" PROTOWRAPPER_API void WFCAPI destoryChannel(const std::string &channelId, fun_general_void_success_callback successBlock, fun_general_void_error_callback errorBlock, void *pObject);

extern "C" PROTOWRAPPER_API const std::string* WFCAPI getAppPath();

extern "C" PROTOWRAPPER_API void WFCAPI getAuthorizedMediaUrl(long long messageUid, int mediaType, const std::string &mediaPath, fun_general_string_success_callback successBlock, fun_general_string_error_callback errorBlock, void *pObj);

}

#endif /* WFClient_h */
