#include "ChatClient.h"
#include "WFClient.h"
#include <mutex>
#include "message/TextMessageContent.h"
#include "message/MessagePayload.h"
#include "message/Message.h"
#include "message/UnknownMessageContent.h"
#include "message/CallStartMessageContent.h"
#include "message/AddGroupMemberNotificationContent.h"
#include "message/CreateGroupNotificationContent.h"
#include "message/DismissGroupNotificationContent.h"
#include "message/ImageMessageContent.h"
#include "message/VideoMessageContent.h"
#include "message/StickerMessageContent.h"
#include "message/KickoffGroupMemberNotificaionContent.h"
#include "message/TipNotificationContent.h"
#include "message/QuitGroupNotificationContent.h"
#include "message/SoundMessageContent.h"
#include "message/FileMessageContent.h"
#include "message/PTextMessageContent.h"
#include "message/TypingMessageContent.h"
#include "message/RecallMessageContent.h"
#include "message/LocationMessageContent.h"
#include "message/TransferGroupOwnerNotificationContent.h"
#include "message/ChangeGroupNameNotificationContent.h"
#include "message/ChangeGroupPortraitNotificationContent.h"
#include "message/ModifyGroupAliasNotificationContent.h"
#include "message/GroupMuteNotificationContent.h"
#include "message/GroupPrivateChatNotificationContent.h"
#include "message/GroupSetManagerNotificationContent.h"
#include "message/GroupJoinTypeNotificationContent.h"

#include "JsonTools.h"

namespace WFCLib {

template <typename T>
std::list<T> serializableFromJsonList(const std::string &jsonListStr);


static ConnectionStatusListener *gConnectionStatusListener = NULL;

static void client_connection_callback(int status) {
	if (gConnectionStatusListener) {
		gConnectionStatusListener->onConnectionStatusChanged((ConnectionStatus)status);
	}
}

static ReceiveMessageListener *gReceiveMessageListener = NULL;

static void client_receive_message_callback(const std::string &messages, bool moreMsg) {
    std::list<Message> tmsgs = serializableFromJsonList<Message>(messages);
	if (gReceiveMessageListener) {
		gReceiveMessageListener->onReceiveMessages(tmsgs, moreMsg);
	}
}
static void client_recall_message_callback(const std::string &operatorId, int64_t messageUid) {
	if (gReceiveMessageListener) {
		gReceiveMessageListener->onRecallMessage(operatorId, messageUid);
	}
}
static void client_delete_message_callback(int64_t messageUid) {
	if (gReceiveMessageListener) {
		gReceiveMessageListener->onDeleteMessage(messageUid);
	}
}

static void client_message_delivered_callback(const std::string &str) {

}

static void client_message_readed_callback(const std::string &str) {

}



static UserInfoUpdateListener *gUserInfoUpdateListener = NULL;
void client_userInfo_update_callback(const std::string &userInfos) {
    if (gUserInfoUpdateListener) {
        gUserInfoUpdateListener->onUserInfoUpdated(serializableFromJsonList<UserInfo>(userInfos));
    }
}


static GroupInfoUpdateListener *gGroupInfoUpdateListener = NULL;
void client_groupInfo_update_callback(const std::string &groupInfos) {
    if (gGroupInfoUpdateListener) {
        gGroupInfoUpdateListener->onGroupInfoUpdated(serializableFromJsonList<GroupInfo>(groupInfos));
    }
    
}


static GroupMemberUpdateListener *gGroupMemberUpdateListener = NULL;
void client_groupMembers_update_callback(const std::string &groupId) {
    if (gGroupMemberUpdateListener) {
        gGroupMemberUpdateListener->onGroupMemberUpdated(groupId);
    }
}


static ContactUpdateListener *gContactUpdateListener = NULL;
void client_friendList_update_callback(const std::string &friendList) {
    if (gContactUpdateListener) {
        gContactUpdateListener->onContactUpdated(parseStringList(friendList));
    }
}


static FriendRequestUpdateListener *gFriendRequestUpdateListener = NULL;
void client_friendRequest_update_callback() {
    if (gFriendRequestUpdateListener) {
        gFriendRequestUpdateListener->onFriendRequestUpdated();
    }
}


static UserSettingUpdateListener *gUserSettingUpdateListener = NULL;
void client_user_setting_update_callback() {
    if (gUserSettingUpdateListener) {
        gUserSettingUpdateListener->onUserSettingUpdated();
    }
}

static ChannelInfoUpdateListener *gChannelInfoUpdateListener = NULL;
void client_channelInfo_update_callback(const std::string &channelInfo) {
    if (gChannelInfoUpdateListener) {
        gChannelInfoUpdateListener->onChannelInfoUpdated(serializableFromJsonList<ChannelInfo>(channelInfo));
    }
}


static void client_genernal_void_success_callback(void *pObj) {
    GeneralVoidCallback *callback = (GeneralVoidCallback *)pObj;
    callback->onSuccess();
}

static void client_genernal_void_error_callback(void *pObj, int errorCode) {
    GeneralVoidCallback *callback = (GeneralVoidCallback *)pObj;
    callback->onFailure(errorCode);
}

static void client_genernal_string_success_callback(void *pObj, const std::string &value) {
    GeneralStringCallback *callback = (GeneralStringCallback *)pObj;
    callback->onSuccess(value);
}

static void client_genernal_string_error_callback(void *pObj, int errorCode) {
    GeneralStringCallback *callback = (GeneralStringCallback *)pObj;
    callback->onFailure(errorCode);
}

static void client_get_remote_message_success_callback(void *pObj, const std::string &value) {
    GetRemoteMessageCallback *callback = (GetRemoteMessageCallback *)pObj;
    callback->onSuccess(serializableFromJsonList<Message>(value));
}

static void client_get_remote_message_error_callback(void *pObj, int errorCode) {
    GetRemoteMessageCallback *callback = (GetRemoteMessageCallback *)pObj;
    callback->onFailure(errorCode);
}

ChatClient* ChatClient::Instance() {
	static ChatClient INSTANCE;
	return &INSTANCE;
}

void ChatClient::setConnectionStatusListener(ConnectionStatusListener * listener)
{
	gConnectionStatusListener = listener;
}

void ChatClient::setReceiveMessageListener(ReceiveMessageListener *listener) {
	gReceiveMessageListener = listener;
}

void ChatClient::setUserInfoUpdateListener(UserInfoUpdateListener *listener) {
	gUserInfoUpdateListener = listener;
}

void ChatClient::setGroupInfoUpdateListener(GroupInfoUpdateListener *listener) {
	gGroupInfoUpdateListener = listener;
}

void ChatClient::setGroupMemberUpdateListener(GroupMemberUpdateListener *listener) {
	gGroupMemberUpdateListener = listener;
}

void ChatClient::setContactUpdateListener(ContactUpdateListener *listener) {
	gContactUpdateListener = listener;
}

void ChatClient::setFriendRequestUpdateListener(FriendRequestUpdateListener *listener) {
	gFriendRequestUpdateListener = listener;
}

void ChatClient::setUserSettingUpdateListener(UserSettingUpdateListener *listener) {
	gUserSettingUpdateListener = listener;
}

void ChatClient::setChannelInfoUpdateListener(ChannelInfoUpdateListener *listener) {
	gChannelInfoUpdateListener = listener;
}

void ChatClient::registerMessage(const MessageContentPrototype *prototype)
{
    messageContentFactorys[prototype->getType()] = prototype;
	WFClient::registerMessageFlag(prototype->getType(), prototype->getFlag());
}

const std::string ChatClient::getClientId()
{
	return convertDllString(WFClient::getClientId());
}

bool ChatClient::connect(const std::string & userId, const std::string &token)
{
	WFClient::setConnectionStatusListener(client_connection_callback);
	WFClient::setReceiveMessageListener(client_receive_message_callback, client_recall_message_callback, client_delete_message_callback, client_message_delivered_callback, client_message_readed_callback);
    WFClient::setUserInfoUpdateListener(client_userInfo_update_callback);
    WFClient::setGroupInfoUpdateListener(client_groupInfo_update_callback);
    WFClient::setGroupMemberUpdateListener(client_groupMembers_update_callback);
    WFClient::setFriendUpdateListener(client_friendList_update_callback);
    WFClient::setFriendRequestListener(client_friendRequest_update_callback);
    WFClient::setSettingUpdateListener(client_user_setting_update_callback);
    WFClient::setChannelInfoUpdateListener(client_channelInfo_update_callback);
    
	return WFClient::connect(userId, token);
}

ChatClient::ChatClient()
{
	registerMessage(&TextMessageContent::sPrototype);
    registerMessage(&CallStartMessageContent::sPrototype);
    registerMessage(&AddGroupMemberNotificationContent::sPrototype);
    registerMessage(&CreateGroupNotificationContent::sPrototype);
    registerMessage(&DismissGroupNotificationContent::sPrototype);
    registerMessage(&ImageMessageContent::sPrototype);
    registerMessage(&VideoMessageContent::sPrototype);
    registerMessage(&StickerMessageContent::sPrototype);
    registerMessage(&KickoffGroupMemberNotificaionContent::sPrototype);
    registerMessage(&TipNotificationContent::sPrototype);
    registerMessage(&QuitGroupNotificationContent::sPrototype);
    registerMessage(&SoundMessageContent::sPrototype);
    registerMessage(&FileMessageContent::sPrototype);
    registerMessage(&PTextMessageContent::sPrototype);
    registerMessage(&TypingMessageContent::sPrototype);
    registerMessage(&RecallMessageContent::sPrototype);
    registerMessage(&LocationMessageContent::sPrototype);
    registerMessage(&TransferGroupOwnerNotificationContent::sPrototype);
    registerMessage(&ChangeGroupNameNotificationContent::sPrototype);
    registerMessage(&ChangeGroupPortraitNotificationContent::sPrototype);
    registerMessage(&ModifyGroupAliasNotificationContent::sPrototype);
    registerMessage(&GroupMuteNotificationContent::sPrototype);
    registerMessage(&GroupPrivateChatNotificationContent::sPrototype);
    registerMessage(&GroupSetManagerNotificationContent::sPrototype);
    registerMessage(&GroupJoinTypeNotificationContent::sPrototype);
}

bool ChatClient::disconnect()
{
	WFClient::disconnect(false);
	return false;
}

bool ChatClient::isLogined() {
    return WFClient::isLogin();
}

ConnectionStatus ChatClient::getConnectionStatus() {
    return (ConnectionStatus)WFClient::getConnectionStatus();
}
const std::string ChatClient::getCurrentUserId() {
    return convertDllString(WFClient::getCurrentUserId());
}

int64_t ChatClient::getServerDeltaTime() {
    return WFClient::getServerDeltaTime();
}

ChatClient::~ChatClient()
{
}

const std::string ChatClient::convertDllString(const std::string * pDllString)
{
	const std::string ret(*pDllString);
	WFClient::releaseDllString(pDllString);
	return ret;
}

MessageContent* ChatClient::getContent(const MessagePayload &payload) {
    const MessageContentPrototype *prototype = messageContentFactorys[payload.contentType];
    MessageContent *content;
    if (prototype) {
        content = prototype->productEmptyContent();
    } else {
        content = new UnknownMessageContent();
    }
    content->decode(payload);
    return content;
}

const std::list<ConversationInfo> ChatClient::getConversationInfos(const std::list<int> &conversationTypes, const std::list<int> &lines) {
    std::string str = convertDllString(WFClient::getConversationInfos(conversationTypes, lines));
    return serializableFromJsonList<ConversationInfo>(str);
}


const ConversationInfo ChatClient::getConversationInfo(const Conversation &conversation) {
    std::string str = convertDllString(WFClient::getConversationInfo(conversation.conversationType, conversation.target, conversation.line));
    ConversationInfo conversationInfo;
    conversationInfo.fromJson(str);
    return conversationInfo;
}

const std::list<ConversationSearchInfo> ChatClient::searchConversation(const std::string &keyword, const std::list<int> &conversationTypes, const std::list<int> &lines) {
    std::string str = convertDllString(WFClient::searchConversation(conversationTypes, lines, keyword));

    return serializableFromJsonList<ConversationSearchInfo>(str);
}

void ChatClient::removeConversation(const Conversation &conversation,bool clearMessage) {
    WFClient::removeConversation(conversation.conversationType, conversation.target, conversation.line, clearMessage);
}

void ChatClient::setConversationTop(const Conversation &conversation, bool top, GeneralVoidCallback *callback) {
    WFClient::setConversationTop(conversation.conversationType, conversation.target, conversation.line, top, client_genernal_void_success_callback,client_genernal_void_error_callback, callback);
}

void ChatClient::setConversationSilent(const Conversation &conversation, bool silent, GeneralVoidCallback *callback) {
    WFClient::setConversationSlient(conversation.conversationType, conversation.target, conversation.line, silent, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::setConversationDraft(const Conversation &conversation, const std::string &draft) {
    WFClient::setConversationDraft(conversation.conversationType, conversation.target, conversation.line, draft);
}

UnreadCount ChatClient::getUnreadCount(const std::list<int> &conversationTypes, const std::list<int> &lines) {
    const std::string str = convertDllString(WFClient::getUnreadCount(conversationTypes, lines));
    UnreadCount uc;
    uc.fromJson(str);
    return uc;
}

UnreadCount ChatClient::getUnreadCount(const Conversation &conversation) {
    const std::string str = convertDllString(WFClient::getConversationUnreadCount(conversation.conversationType, conversation.target, conversation.line));
    UnreadCount uc;
    uc.fromJson(str);
    return uc;
}

void ChatClient::clearUnreadStatus(const Conversation &conversation) {
    WFClient::clearUnreadStatus(conversation.conversationType, conversation.target, conversation.line);
}

void ChatClient::clearUnreadStatus(const std::list<int> &conversationTypes, const std::list<int> &lines) {
    WFClient::clearUnreadStatus(conversationTypes, lines);
}

void ChatClient::clearAllUnreadStatus() {
    WFClient::clearAllUnreadStatus();
}

void ChatClient::setMediaMessagePlayed(long messageId) {
    WFClient::setMediaMessagePlayed(messageId);
}

const std::list<Message> ChatClient::getMessages(const Conversation &conversation, const std::list<int> &contentTypes, int64_t fromIndex,int count, const std::string &user) {
    std::string str = convertDllString(WFClient::getMessages(conversation.conversationType, conversation.target, conversation.line, contentTypes, fromIndex, count>0, abs(count), user));

    return serializableFromJsonList<Message>(str);
}

const std::list<Message> ChatClient::getMessages(const std::list<int> &conversationTypes, const std::list<int> &lines, const std::list<int> &contentTypes, int64_t fromIndex, int count, const std::string &user) {
    std::string str = convertDllString(WFClient::getMessages(conversationTypes, lines, contentTypes, fromIndex, count>0, abs(count), user));

    return serializableFromJsonList<Message>(str);
}

const std::list<Message> ChatClient::getMessages(const std::list<int> &conversationTypes, const std::list<int> &lines, MessageStatus messageStatus, int64_t fromIndex, int count, const std::string &user) {
    std::string str = convertDllString(WFClient::getMessages(conversationTypes, lines, messageStatus, fromIndex, count>0, abs(count), user));

    return serializableFromJsonList<Message>(str);
}

void ChatClient::getRemoteMessages(const Conversation &conversation, int64_t beforeMessageUid, int count, GetRemoteMessageCallback *callback) {
    WFClient::getRemoteMessages(conversation.conversationType, conversation.target, conversation.line, beforeMessageUid, count, client_get_remote_message_success_callback, client_get_remote_message_error_callback, callback);
}

const Message ChatClient::getMessage(long messageId) {
    std::string str = convertDllString(WFClient::getMessage(messageId));
    Message message;
    message.fromJson(str);
    return message;
}

const Message ChatClient::getMessageByUid(int64_t messageUid) {
    std::string str = convertDllString(WFClient::getMessageByUid(messageUid));
    Message message;
    message.fromJson(str);
    return message;
}

const std::list<Message> ChatClient::searchMessage(const Conversation &conversation, const std::string &keyword, int count) {
    return serializableFromJsonList<Message>(convertDllString(WFClient::searchMessage(conversation.conversationType, conversation.target, conversation.line, keyword, count)));
}

void client_sendMessage_success_callback(void *pObject, int64_t messageUid, int64_t timestamp) {
    if (pObject) {
        WFSendMessageCallback *callback = (WFSendMessageCallback *)pObject;
        callback->onSuccess(messageUid, timestamp);
    }
}

void client_sendMessage_progress_callback(void *pObject, int uploaded, int total) {
    if (pObject) {
        WFSendMessageCallback *callback = (WFSendMessageCallback *)pObject;
        callback->onProgress(uploaded, total);
    }
}

void client_sendMessage_error_callback(void *pObject, int errorCode) {
    if (pObject) {
        WFSendMessageCallback *callback = (WFSendMessageCallback *)pObject;
        callback->onFailure(errorCode);
    }
}

const Message ChatClient::sendMessage(const Conversation &conversation, const MessageContent &content, const std::list<std::string> &toUsers, int expireDuration, WFSendMessageCallback *callback) {
    std::string str = convertDllString(WFClient::sendMessage(conversation.conversationType, conversation.target, conversation.line, content.encode().toJson(), toUsers, expireDuration, client_sendMessage_success_callback, client_sendMessage_error_callback, client_sendMessage_progress_callback, callback))
    ;
    Message message;
    message.fromJson(str);
    return message;
}

void ChatClient::recallMessage(int64_t messageUid, GeneralVoidCallback *callback) {
    WFClient::recallMessage(messageUid, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void client_uploadMedia_success_callback(void *pObject, const std::string &remoteUrl) {
    if (pObject) {
        UploadMediaCallback *callback = (UploadMediaCallback *)pObject;
        callback->onSuccess(remoteUrl);
    }
}

void client_uploadMedia_progress_callback(void *pObject, int uploaded, int total) {
    if (pObject) {
        UploadMediaCallback *callback = (UploadMediaCallback *)pObject;
        callback->onProgress(uploaded, total);
    }
}

void client_uploadMedia_error_callback(void *pObject, int errorCode) {
    if (pObject) {
        UploadMediaCallback *callback = (UploadMediaCallback *)pObject;
        callback->onFailure(errorCode);
    }
}

void ChatClient::uploadMedia(const std::string &fileName, const std::string mediaData, MediaType mediaType, UploadMediaCallback *callback) {
    WFClient::uploadMedia(fileName, mediaData.c_str(), (int)mediaData.length(), mediaType, client_uploadMedia_success_callback, client_uploadMedia_error_callback, client_uploadMedia_progress_callback, callback);
}

bool ChatClient::deleteMessage(long messageId) {
    return WFClient::deleteMessage(messageId);
}


void ChatClient::clearMessages(const Conversation &conversation) {
    WFClient::clearMessages(conversation.conversationType, conversation.target, conversation.line);
}

void ChatClient::clearMessages(const Conversation &conversation, int64_t before) {
    WFClient::clearMessages(conversation.conversationType, conversation.target, conversation.line, before);
}

const Message ChatClient::insert(const Conversation &conversation, const std::string &sender, const MessageContent &content, MessageStatus status, bool notify, int64_t serverTime) {
    std::string str = convertDllString(WFClient::insertMessage(conversation.conversationType, conversation.target, conversation.line, sender, content.encode().toJson(), status, notify, serverTime));
    Message message;
    message.fromJson(str);
    return message;
}

void ChatClient::updateMessage(long messageId, const MessageContent &content) {
    WFClient::updateMessage(messageId, content.encode().toJson());
}

const UserInfo ChatClient::getUserInfo(const std::string &userId, bool refresh) {
    return getUserInfo(userId, "", refresh);
}

const UserInfo ChatClient::getUserInfo(const std::string &userId, const std::string &groupId, bool refresh) {
    std::string str = convertDllString(WFClient::getUserInfo(userId, refresh, groupId));
    UserInfo userInfo;
    userInfo.fromJson(str);
    return userInfo;
}

const std::list<UserInfo> ChatClient::getUserInfos(std::list<std::string> &userIds, const std::string &groupId) {
    std::string str = convertDllString(WFClient::getUserInfos(userIds, groupId));
    return serializableFromJsonList<UserInfo>(str);
}

static void client_searchUser_success_callback(void *pObj, const std::string &value) {
    if (pObj) {
        SearchUserCallback *callback = (SearchUserCallback *)pObj;
        callback->onSuccess(serializableFromJsonList<UserInfo>(value));
    }
}

static void client_searchUser_error_callback(void *pObj, int errorCode) {
    if (pObj) {
        SearchUserCallback *callback = (SearchUserCallback *)pObj;
        callback->onFailure(errorCode);
    }
}

void ChatClient::searchUser(const std::string &keyword, SearchUserType searchType, int page, SearchUserCallback *callback) {
    WFClient::searchUser(keyword, searchType, page, client_searchUser_success_callback, client_searchUser_error_callback, callback);
}

bool ChatClient::isMyFriend(const std::string &userId) {
    return WFClient::isMyFriend(userId);
}

const std::list<std::string> ChatClient::getMyFriendList(bool refresh) {
    std::string str = convertDllString(WFClient::getMyFriendList(refresh));
    return parseStringList(str);
}

const std::list<UserInfo> ChatClient::searchFriends(const std::string &keyword) {
    std::string str = convertDllString(WFClient::searchFriends(keyword));
    return serializableFromJsonList<UserInfo>(str);
}


const std::list<GroupSearchInfo> ChatClient::searchGroups(const std::string &keyword) {
    std::string str = convertDllString(WFClient::searchGroups(keyword));
    return serializableFromJsonList<GroupSearchInfo>(str);
}

const std::list<FriendRequest> ChatClient::getIncommingFriendRequest() {
    std::string str = convertDllString(WFClient::getIncommingFriendRequest());
    return serializableFromJsonList<FriendRequest>(str);
}

const std::list<FriendRequest> ChatClient::getOutgoingFriendRequest() {
    std::string str = convertDllString(WFClient::getOutgoingFriendRequest());
    return serializableFromJsonList<FriendRequest>(str);
}

void ChatClient::loadFriendRequestFromRemote() {
    WFClient::loadFriendRequestFromRemote();
}

int ChatClient::getUnreadFriendRequestStatus() {
    return WFClient::getUnreadFriendRequestStatus();
}

void ChatClient::clearUnreadFriendRequestStatus() {
    WFClient::clearUnreadFriendRequestStatus();
}

void ChatClient::deleteFriend(const std::string &userId, GeneralVoidCallback *callback) {
    WFClient::deleteFriend(userId, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::sendFriendRequest(const std::string &userId, const std::string &reason, GeneralVoidCallback *callback) {
    WFClient::sendFriendRequest(userId, reason, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::handleFriendRequest(const std::string &userId, bool accpet, const std::string &friendExtra, GeneralVoidCallback *callback) {
    WFClient::handleFriendRequest(userId, accpet, friendExtra, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

const std::string ChatClient::getFriendAlias(const std::string &userId) {
    return convertDllString(WFClient::getFriendAlias(userId));
}

void ChatClient::setFriend(const std::string &userId, const std::string &alias, GeneralVoidCallback *callback) {
    WFClient::setFriendAlias(userId, alias, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

bool ChatClient::isBlackListed(const std::string &userId) {
    return WFClient::isBlackListed(userId);
}

const std::list<std::string> ChatClient::getBlackList(bool refresh) {
    return parseStringList(convertDllString(WFClient::getBlackList(refresh)));
}

void ChatClient::setBlackList(const std::string &userId, bool isBlackListed, GeneralVoidCallback *callback) {
    WFClient::setBlackList(userId, isBlackListed, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

const std::list<GroupMember> ChatClient::getGroupMembers(const std::string &groupId, bool forceUpdate) {
    std::string str = convertDllString(WFClient::getGroupMembers(groupId, forceUpdate));
    return serializableFromJsonList<GroupMember>(str);
}

const GroupInfo ChatClient::getGroupInfo(const std::string &groupId, bool refresh) {
    std::string str = convertDllString(WFClient::getGroupInfo(groupId, refresh));
    GroupInfo groupInfo;
    groupInfo.fromJson(str);
    return groupInfo;
}

const GroupMember ChatClient::getGroupMember(const std::string &groupId, const std::string &memberId) {
   std::string str = convertDllString(WFClient::getGroupMember(groupId, memberId));
   GroupMember member;
   member.fromJson(str);
   return member;
}

void ChatClient::createGroup(const std::string &groupId, const std::string &groupName, const std::string &groupPortrait, GroupType type, const std::list<std::string> &groupMembers, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralStringCallback *callback) {

    WFClient::createGroup(groupId, type, groupName, groupPortrait, groupMembers, notifyLines, notifyContent.encode().toJson(), client_genernal_string_success_callback, client_genernal_string_error_callback, callback);
}

void ChatClient::addMembers(const std::list<std::string> &members, const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::addMembers(groupId, members, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::kickoffMembers(const std::list<std::string> &members, const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::kickoffMembers(groupId, members, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::quitGroup(const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::quitGroup(groupId, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::dismissGroup(const std::string &groupId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::dismissGroup(groupId, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);;
}

void ChatClient::modifyGroupInfo(const std::string &groupId, ModifyGroupInfoType type, const std::string &newValue, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::modifyGroupInfo(groupId, type, newValue, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::modifyGroupAlias(const std::string &groupId, const std::string &newAlias, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::modifyGroupAlias(groupId, newAlias, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::transferGroup(const std::string &groupId, const std::string &newOwner, const std::list<int> &notifyLines, const MessageContent &notifyContent,  GeneralVoidCallback *callback) {
    WFClient::transferGroup(groupId, newOwner, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::setGroupManager(const std::string &groupId, bool isSet, const std::list<std::string> &memberId, const std::list<int> &notifyLines, const MessageContent &notifyContent, GeneralVoidCallback *callback) {
    WFClient::setGroupManager(groupId, isSet, memberId, notifyLines, notifyContent.encode().toJson(), client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

const std::list<std::string> ChatClient::getFavGroups() {
    return parseStringList(convertDllString(WFClient::getFavGroups()));
}

bool ChatClient::isFavGroup(const std::string &groupId) {
    return WFClient::isFavGroup(groupId);
}

void ChatClient::setFavGroup(const std::string &groupId, bool fav, GeneralVoidCallback *callback) {
    WFClient::setFavGroup(groupId, fav, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

const std::string ChatClient::getUserSetting(UserSettingScope scope, const std::string &key) {
    return convertDllString(WFClient::getUserSetting(scope, key));
}

std::map<std::string, std::string> convertStr2MapList(const std::string &str) {
    std::map<std::string, std::string> strMap;

    Document document;
    if (document.Parse(str).HasParseError()) {
        printf("\nParsing to document failure(%s).\n", str.c_str());
        return strMap;
    }

    if (document.IsArray()) {
        for (int i = 0; i < document.Size(); i++) {
            const Value& object = document[i];
            std::string key;
            std::string value;
            getValue(object, "key", key);
            getValue(object, "value", value);
            strMap[key] = value;
        }
    }

    return strMap;
}

const std::map<std::string, std::string> ChatClient::getUserSettings(UserSettingScope scope) {
    std::string str = convertDllString(WFClient::getUserSettings(scope));
    return convertStr2MapList(str);
}

void ChatClient::setUserSetting(UserSettingScope scope, const std::string &key, const std::string &value, GeneralVoidCallback *callback) {
    WFClient::setUserSetting(scope, key, value, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::modifyMyInfo(const std::list<std::pair<int, std::string> > &infos, GeneralVoidCallback *callback) {
    WFClient::modifyMyInfo(infos, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

bool ChatClient::isGlobalSlient() {
    return WFClient::isGlobalSlient();
}

void ChatClient::setGlobalSlient(bool slient, GeneralVoidCallback *callback) {
    WFClient::setGlobalSlient(slient, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

bool ChatClient::isHiddenNotificationDetail() {
    return WFClient::isHiddenNotificationDetail();
}

void ChatClient::setHiddenNotificationDetail(bool hidden, GeneralVoidCallback *callback) {
    WFClient::setHiddenNotificationDetail(hidden, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::setHiddenGroupMemberName(bool hidden, const std::string &groupId, GeneralVoidCallback *callback) {
    WFClient::setHiddenGroupMemberName(groupId, hidden, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::joinChatroom(const std::string &chatroomId, GeneralVoidCallback *callback) {
    WFClient::joinChatroom(chatroomId, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::quitChatroom(const std::string &chatroomId, GeneralVoidCallback *callback) {
    WFClient::quitChatroom(chatroomId, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

static void client_get_chatroomInfo_success_callback(void *pObj, const std::string &value) {
    if (pObj) {
        GetChatroomInfoCallback *callback = (GetChatroomInfoCallback *)pObj;
        ChatroomInfo info;
        info.fromJson(value);
        callback->onSuccess(info);
    }
}

static void client_get_chatroomInfo_error_callback(void *pObj, int errorCode) {
    if(pObj) {
        GetChatroomInfoCallback *callback = (GetChatroomInfoCallback *)pObj;
        callback->onFailure(errorCode);
    }
}

void ChatClient::getChatroomInfo(const std::string &chatroomId, int64_t updateDt, GetChatroomInfoCallback *callback) {
    WFClient::getChatroomInfo(chatroomId, updateDt, client_get_chatroomInfo_success_callback, client_get_chatroomInfo_error_callback, callback);
}

static void client_get_chatroomMemberInfo_success_callback(void *pObj, const std::string &value) {
    if (pObj) {
        GetChatroomMemberInfoCallback *callback = (GetChatroomMemberInfoCallback *)pObj;
        ChatroomMemberInfo info;
        info.fromJson(value);
        callback->onSuccess(info);
    }
}

static void client_get_chatroomMemberInfo_error_callback(void *pObj, int errorCode) {
    if(pObj) {
        GetChatroomMemberInfoCallback *callback = (GetChatroomMemberInfoCallback *)pObj;
        callback->onFailure(errorCode);
    }
}


void ChatClient::getChatroomMemberInfo(const std::string &chatroomId, int maxCount, GetChatroomMemberInfoCallback *callback) {
    WFClient::getChatroomMemberInfo(chatroomId, maxCount, client_get_chatroomMemberInfo_success_callback, client_get_chatroomMemberInfo_error_callback, callback);
}


static void client_get_channelInfo_success_callback(void *pObj, const std::string &value) {
    if (pObj) {
        GetChannelInfoCallback *callback = (GetChannelInfoCallback *)pObj;
        ChannelInfo info;
        info.fromJson(value);
        callback->onSuccess(info);
    }
}

static void client_get_channelInfo_error_callback(void *pObj, int errorCode) {
    if(pObj) {
        GetChannelInfoCallback *callback = (GetChannelInfoCallback *)pObj;
        callback->onFailure(errorCode);
    }
}

void ChatClient::createChannel(const std::string &channelName, const std::string &channelPortrait, int status, const std::string &desc, const std::string &extra, GetChannelInfoCallback *callback) {
    WFClient::createChannel(channelName, channelPortrait, status, desc, extra, client_get_channelInfo_success_callback, client_get_channelInfo_error_callback, callback);
}

ChannelInfo ChatClient::getChannelInfo(const std::string &channelId, bool refresh) {
    std::string str = convertDllString(WFClient::getChannelInfo(channelId, refresh));
    ChannelInfo channelInfo;
    channelInfo.fromJson(str);
    return channelInfo;
}

void ChatClient::modifyChannelInfo(const std::string &channelId, ModifyChannelInfoType type, const std::string &newValue, GeneralVoidCallback *callback) {
    WFClient::modifyChannelInfo(channelId, type, newValue, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

static void client_search_channel_success_callback(void *pObj, const std::string &value) {
    if (pObj) {
        SearchChannelCallback *callback = (SearchChannelCallback *)pObj;
        callback->onSuccess(serializableFromJsonList<ChannelInfo>(value));
    }
}

static void client_search_channel_error_callback(void *pObj, int errorCode) {
    if(pObj) {
        SearchChannelCallback *callback = (SearchChannelCallback *)pObj;
        callback->onFailure(errorCode);
    }
}

void ChatClient::searchChannel(const std::string &keyword, SearchChannelCallback *callback) {
    WFClient::searchChannel(keyword, client_search_channel_success_callback, client_search_channel_error_callback, callback);
}

bool ChatClient::isListenedChannel(const std::string &channelId) {
    return WFClient::isListenedChannel(channelId);
}

void ChatClient::listenChannel(const std::string &channelId, bool listen, GeneralVoidCallback *callback) {
    WFClient::listenChannel(channelId, listen, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

const std::list<std::string> ChatClient::getMyChannels() {
    return parseStringList(convertDllString(WFClient::getMyChannels()));
}

const std::list<std::string> ChatClient::getListenedChannels() {
    return parseStringList(convertDllString(WFClient::getListenedChannels()));
}

void ChatClient::destoryChannel(const std::string &channelId, GeneralVoidCallback *callback) {
    WFClient::destoryChannel(channelId, client_genernal_void_success_callback, client_genernal_void_error_callback, callback);
}

void ChatClient::getAuthorizedMediaUrl(int mediaType, const std::string &mediaPath, GeneralStringCallback *callback) {
	WFClient::getAuthorizedMediaUrl(mediaType, mediaPath, client_genernal_string_success_callback, client_genernal_string_error_callback, callback);
}

template <typename T>
std::list<T> serializableFromJsonList(const std::string &jsonListStr) {
    Document document;
    if (document.Parse(jsonListStr).HasParseError()) {
        printf("\nParsing to document failure(%s).\n", jsonListStr.c_str());
        return std::list<T>();
    }

    std::list<T> result;

    if (document.IsArray()) {
        for (int i = 0; i < document.Size(); i++) {
            const Value& object = document[i];
            T message;
            Serializable *s = &message;
            s->Unserialize(&object);

            result.push_back(message);
        }
    }

    return result;
}
};
