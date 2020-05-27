// ClrChatClient.h

#pragma once

#include "WFClient.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;
using namespace System::Reflection;

using System::Reflection::TypeInfo;
using System::Runtime::InteropServices::Marshal;

namespace ClrChatClient {

	public delegate void OnConnectionStatusListenerDelegate(int);
	public delegate void OnReceiveMessageDelegate(System::String^ messages, bool hasMore);
	public delegate void OnRecallMessageDelegate(Int64 messageUid);
	public delegate void OnDeleteMessageDelegate(Int64 messageUid);
	public delegate void OnMessageDeliveredDelegate(System::String^ deliveryStr);
	public delegate void OnMessageReadedDelegate(System::String^ readedStr);
	public delegate void OnStringDelegate(System::String^ str);
	public delegate void OnVoidDelegate();

	public delegate void onErrorCallbackDelegate(int);
	public delegate void onGeneralVoidSuccessCallbackDelegate();
	public delegate void onGeneralStringSuccessCallbackDelegate(System::String^);
	public delegate void onIntIntCallbackDelegate(int, int);
	public delegate void onBigIntBigIntCallbackDelegate(Int64, Int64);

	public delegate void OnNativeReceiveMessageDelegate(const std::string &messages, bool hasMore);
	public delegate void OnNativeRecallMessageDelegate(const std::string &operatorId, int64_t messageUid);
	public delegate void OnNativeDeleteMessageDelegate(int64_t messageUid);
	public delegate void OnNativeMessageDeliveredDelegate(const std::string &str);
	public delegate void OnNativeMessageReadedDelegate(const std::string &str);
	public delegate void OnNativeStringDelegate(const std::string &str);

	public ref class Proto
	{
		// TODO: Add your methods for this class here.
	public:
		Proto() {

		}
		
		System::String^ getClientId() {
			const std::string *stdStr = WFClient::getClientId();
			return ConvertStr(stdStr);
		}

		void setConnectStatusListener(OnConnectionStatusListenerDelegate^ listener) { 
			m_OnConnectionStatusListenerDelegate = listener;  
			IntPtr ip = Marshal::GetFunctionPointerForDelegate(m_OnConnectionStatusListenerDelegate);
			WFClient::setConnectionStatusListener(static_cast<WFClient::fun_connection_callback>(ip.ToPointer()));
		}

		void setMessageListener(OnReceiveMessageDelegate^ receiveListener, OnRecallMessageDelegate^ recallListener, OnDeleteMessageDelegate^ deleteListener, OnMessageDeliveredDelegate^ deliveryListener, OnMessageReadedDelegate^ readedListener) {
			m_OnReceiveMessageDelegate = receiveListener;
			m_OnRecallMessageDelegate = recallListener;
			m_OnDeleteMessageDelegate = deleteListener;

			m_OnMessageDeliveredDelegate = deliveryListener;
			m_OnMessageReadedDelegate = readedListener;
		}

		void setUserInfoUpdateListener(OnStringDelegate^ listener) {
			m_onUserInfoUpdateListener = listener;	
		}

		void setGroupInfoUpdateListener(OnStringDelegate^ listener) {
			m_onGroupInfoUpdateListener = listener;
		}

		void setGroupMemberUpdateListener(OnStringDelegate^ listener) {
			m_onGroupMemberUpdateListener = listener;
		}

		void setContactUpdateListener(OnStringDelegate^ listener) {
			m_onContactUpdateListener = listener;
		}


		OnVoidDelegate^ m_NativeFriendRequestUpdateDelegate;
		void setFriendRequestUpdateListener(OnVoidDelegate^ listener) {
			m_NativeFriendRequestUpdateDelegate = listener;
			IntPtr ip = Marshal::GetFunctionPointerForDelegate(listener);
			WFClient::setFriendRequestListener(static_cast<WFClient::fun_receive_friendRequest_callback>(ip.ToPointer()));
		}

		OnVoidDelegate^ m_NativeSettingUpdateDelegate;
		void setUserSettingUpdateListener(OnVoidDelegate^ listener) {
			m_NativeSettingUpdateDelegate = listener;
			IntPtr ip = Marshal::GetFunctionPointerForDelegate(listener);
			WFClient::setSettingUpdateListener(static_cast<WFClient::fun_user_setting_update_callback>(ip.ToPointer()));
		}

		void setChannelInfoUpdateListener(OnStringDelegate^ listener) {
			m_onChannelInfoUpdateListener = listener;
		}

		OnNativeStringDelegate^ m_NativeUserInfoUpdateDelegate;
		OnNativeStringDelegate^ m_NativeGroupInfoDelegate;
		OnNativeStringDelegate^ m_NativeGroupMemberDelegate;
		OnNativeStringDelegate^ m_NativeContactUpdateDelegate;
		OnNativeStringDelegate^ m_NativeChannelInfoUpdateDelegate;
		OnNativeReceiveMessageDelegate^ m_NativeReceiveMessageDelegate;
		OnNativeRecallMessageDelegate^ m_NativeRecallMessageDelegate;
		OnNativeDeleteMessageDelegate^ m_NativeDeleteMessageDelegate;

		OnNativeMessageDeliveredDelegate^ m_NativeMessageDeliveredDelegate;
		OnNativeMessageReadedDelegate^ m_NativeMessageReadedDelegate;

		bool connect(System::String^ userId, System::String^ token) {
			m_NativeReceiveMessageDelegate = gcnew OnNativeReceiveMessageDelegate(this, &Proto::onReceiveMessage);
			IntPtr ip1 = Marshal::GetFunctionPointerForDelegate(m_NativeReceiveMessageDelegate);
			m_NativeRecallMessageDelegate = gcnew OnNativeRecallMessageDelegate(this, &Proto::onRecallMessage);
			IntPtr ip2 = Marshal::GetFunctionPointerForDelegate(m_NativeRecallMessageDelegate);
			m_NativeDeleteMessageDelegate = gcnew OnNativeDeleteMessageDelegate(this, &Proto::onDeleteMessage);
			IntPtr ip21 = Marshal::GetFunctionPointerForDelegate(m_NativeDeleteMessageDelegate);

			m_NativeMessageDeliveredDelegate = gcnew OnNativeMessageDeliveredDelegate(this, &Proto::onMessageDelivered);
			IntPtr ip22 = Marshal::GetFunctionPointerForDelegate(m_NativeMessageDeliveredDelegate);
			m_NativeMessageReadedDelegate = gcnew OnNativeMessageReadedDelegate(this, &Proto::onMessageReaded);
			IntPtr ip23 = Marshal::GetFunctionPointerForDelegate(m_NativeMessageReadedDelegate);

			WFClient::setReceiveMessageListener(static_cast<WFClient::fun_receive_message_callback>(ip1.ToPointer()), static_cast<WFClient::fun_recall_message_callback>(ip2.ToPointer()), static_cast<WFClient::fun_delete_message_callback>(ip21.ToPointer()), static_cast<WFClient::fun_message_receipt_callback>(ip22.ToPointer()), static_cast<WFClient::fun_message_receipt_callback>(ip23.ToPointer()));

			m_NativeUserInfoUpdateDelegate = gcnew OnNativeStringDelegate(this, &Proto::onUserInfoUpdate);
			IntPtr ipUserinfo = Marshal::GetFunctionPointerForDelegate(m_NativeUserInfoUpdateDelegate);
			WFClient::setUserInfoUpdateListener(static_cast<WFClient::fun_userInfo_update_callback>(ipUserinfo.ToPointer()));

			m_NativeGroupInfoDelegate = gcnew OnNativeStringDelegate(this, &Proto::onGroupInfoUpdate);
			IntPtr ip3 = Marshal::GetFunctionPointerForDelegate(m_NativeGroupInfoDelegate);
			WFClient::setGroupInfoUpdateListener(static_cast<WFClient::fun_groupInfo_update_callback>(ip3.ToPointer()));


			m_NativeGroupMemberDelegate = gcnew OnNativeStringDelegate(this, &Proto::onGroupMemberUpdate);
			IntPtr ip4 = Marshal::GetFunctionPointerForDelegate(m_NativeGroupMemberDelegate);
			WFClient::setGroupMemberUpdateListener(static_cast<WFClient::fun_groupMembers_update_callback>(ip4.ToPointer()));


			m_NativeContactUpdateDelegate = gcnew OnNativeStringDelegate(this, &Proto::onContactUpdate);
			IntPtr ip5 = Marshal::GetFunctionPointerForDelegate(m_NativeContactUpdateDelegate);
			WFClient::setFriendUpdateListener(static_cast<WFClient::fun_friendList_update_callback>(ip5.ToPointer()));


			m_NativeChannelInfoUpdateDelegate = gcnew OnNativeStringDelegate(this, &Proto::onChannelInfoUpdate);
			IntPtr ip6 = Marshal::GetFunctionPointerForDelegate(m_NativeChannelInfoUpdateDelegate);
			WFClient::setChannelInfoUpdateListener(static_cast<WFClient::fun_userInfo_update_callback>(ip6.ToPointer()));

			const char* uid = (const char*)(Marshal::StringToHGlobalAnsi(userId)).ToPointer();
			const char* tk = (const char*)(Marshal::StringToHGlobalAnsi(token)).ToPointer();
			return WFClient::connect(uid, tk);
		}

		void disconnect() {
			WFClient::disconnect(0);
		}

		bool isLogined() {
			return WFClient::isLogin();
		}

		int getConnectionStatus() {
			return WFClient::getConnectionStatus();
		}

		System::String^ getCurrentUserId() {
			return ConvertStr(WFClient::getCurrentUserId());
		}

		void registerMessageFlag(int type, int flag) {
			WFClient::registerMessageFlag(type, flag);
		}

		Int64 getServerDeltaTime() {
			return WFClient::getServerDeltaTime();
		}

		System::String^ getConversationInfos(List<int>^ types, List<int>^ lines) {
			std::list<int> ts;
			for each (int type in types)
			{
				ts.push_back(type);
			}

			std::list<int> ls;
			for each (int line in lines)
			{
				ls.push_back(line);
			}
			if (ls.size() == 0) {
				ls.push_back(0);
			}
			
			return ConvertStr(WFClient::getConversationInfos(ts, ls));
		}

		System::String^ getConversationInfo(int type, System::String^ target, int line) {
			return ConvertStr(WFClient::getConversationInfo(type, ConvertStr(target), line));
		}

		System::String^ searchConversation(System::String^ keyword, List<int>^ types, List<int>^ lines) {
			std::list<int> ts;
			for each (int type in types)
			{
				ts.push_back(type);
			}

			std::list<int> ls;
			for each (int line in lines)
			{
				ls.push_back(line);
			}
			if (ls.size() == 0) {
				ls.push_back(0);
			}

			return ConvertStr(WFClient::searchConversation(ts, ls, ConvertStr(keyword)));
		}

		void removeConversation(int type, System::String^ target, int line, bool clearMessage) {
			WFClient::removeConversation(type, ConvertStr(target), line, clearMessage);
		}

		void setConversationTop(int type, System::String^ target, int line, bool top, onGeneralVoidSuccessCallbackDelegate^ successCB, onErrorCallbackDelegate^ errorCB);
		void setConversationSilent(int type, System::String^ target, int line, bool silent, onGeneralVoidSuccessCallbackDelegate^ successCB, onErrorCallbackDelegate^ errorCB);
		void setConversationDraft(int type, System::String^ target, int line, System::String^ draft);
		System::String^ getUnreadCount(List<int>^ types, List<int>^ lines);
		System::String^ getUnreadCount(int type, System::String^ target, int line);
		void clearUnreadStatus(int type, System::String^ target, int line);
		void clearUnreadStatus(List<int>^ conversationTypes, List<int>^ lines);
		void clearAllUnreadStatus();
		String^ Proto::getMessageDelivery(int conversationType, String^ target);
		String^ Proto::getConversationRead(int conversationType, String^ target, int line);
		void setMediaMessagePlayed(long messageId);
		System::String^ getMessages(int type, System::String^ target, int line, List<int>^ contentTypes, Int64 fromIndex, int count, System::String^ user);
		System::String^ getMessages(List<int>^ conversationTypes, List<int>^ lines, List<int>^ contentTypes, Int64 fromIndex, int count, System::String^ user);
		System::String^ getMessages(List<int>^ conversationTypes, List<int>^ lines, int messageStatus, Int64 fromIndex, int count, System::String^ user);
		void getRemoteMessages(int type, System::String^ target, int line, Int64 beforeMessageUid, int count, onGeneralStringSuccessCallbackDelegate^ strCB, onErrorCallbackDelegate^ errCB);
		System::String^ getMessage(long messageId);
		System::String^ getMessageByUid(Int64 messageUid);	
		System::String^ searchMessage(int type, System::String^ target, int line, System::String^ keyword, int count);
		
		System::String^ sendMessage(int type, System::String^ target, int line, System::String^ content, List<System::String^>^ toUsers, int expireDuration, onBigIntBigIntCallbackDelegate^ succDele, onIntIntCallbackDelegate^ progressDele, onErrorCallbackDelegate^ errDele);
		void recallMessage(Int64 messageUid, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void uploadMedia(System::String^ fileName, System::String^mediaData, int mediaType, onGeneralStringSuccessCallbackDelegate^ succDele, onIntIntCallbackDelegate^ progressDele, onErrorCallbackDelegate^ errDele);
		bool deleteMessage(long messageId);
		void clearMessages(int type, System::String^ target, int line);
		void clearMessages(int type, System::String^ target, int line, Int64 before);
		System::String^ insert(int type, System::String^ target, int line, System::String^sender, System::String^ content, int status, bool notify, Int64 serverTime);
		void updateMessage(long messageId, System::String^ content);
		System::String^ getUserInfo(System::String^userId, bool refresh);
		System::String^ getUserInfo(System::String^userId, System::String^groupId, bool refresh);
		System::String^ getUserInfos(List< System::String^>^ userIds, System::String^ groupId);
		void searchUser(System::String^keyword, int searchType, int page, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		bool isMyFriend(System::String^userId);
		System::String^ getMyFriendList(bool refresh);
		System::String^ searchFriends(System::String^keyword);
		System::String^ searchGroups(System::String^keyword);
		System::String^ getIncommingFriendRequest();
		System::String^ getOutgoingFriendRequest();
		void loadFriendRequestFromRemote();
		int getUnreadFriendRequestStatus();
		void clearUnreadFriendRequestStatus();
		void deleteFriend(System::String^userId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void sendFriendRequest(System::String^userId, System::String^reason, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void handleFriendRequest(System::String^userId, bool accpet, System::String^friendExtra, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		System::String^ getFriendAlias(System::String^userId);
		void setFriendAlias(System::String^userId, System::String^alias, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		bool isBlackListed(System::String^userId);
		System::String^ getBlackList(bool refresh);
		void setBlackList(System::String^userId, bool isBlackListed, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		System::String^ getGroupMembers(System::String^groupId, bool forceUpdate);
		System::String^ getGroupInfo(System::String^groupId, bool refresh);
		System::String^ getGroupMember(System::String^groupId, System::String^memberId);
		void createGroup(System::String^groupId, System::String^groupName, System::String^groupPortrait, int type, List<System::String^>^ groupMembers, List<int>^ notifyLines, System::String^ notifyContent, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void addMembers(List<System::String^>^ members, System::String^groupId, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void kickoffMembers(List<System::String^>^ members, System::String^groupId, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void quitGroup(System::String^groupId, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void dismissGroup(System::String^groupId, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void modifyGroupInfo(System::String^groupId, int type, System::String^newValue, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void modifyGroupAlias(System::String^groupId, System::String^newAlias, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void transferGroup(System::String^groupId, System::String^newOwner, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void setGroupManager(System::String^groupId, bool isSet, List<System::String^>^ memberIds, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void muteGroupMember(System::String^groupId, bool isSet, List<System::String^>^ memberIds, List<int>^ notifyLines, System::String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);

		System::String^ getFavGroups();
		bool isFavGroup(System::String^groupId);
		void setFavGroup(System::String^groupId, bool fav, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		System::String^ getUserSetting(int scope, System::String^key);
		System::String^ getUserSettings(int scope);
		void setUserSetting(int scope, System::String^key, System::String^value, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void modifyMyInfo(Dictionary<int, String^>^ values, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		bool isGlobalSlient();
		void setGlobalSlient(bool slient, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		bool isHiddenNotificationDetail();
		void setHiddenNotificationDetail(bool hidden, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void setHiddenGroupMemberName(bool hidden, System::String^groupId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void joinChatroom(System::String^chatroomId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void quitChatroom(System::String^chatroomId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void getChatroomInfo(System::String^chatroomId, Int64 updateDt, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void getChatroomMemberInfo(System::String^chatroomId, int maxCount, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void createChannel(System::String^channelName, System::String^channelPortrait, int status, System::String^desc, System::String^extra, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		System::String^ getChannelInfo(System::String^channelId, bool refresh);
		void modifyChannelInfo(System::String^channelId, int type, System::String^newValue, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void searchChannel(System::String^keyword, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		bool isListenedChannel(System::String^channelId);
		void listenChannel(System::String^channelId, bool listen, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		System::String^ getMyChannels();
		System::String^ getListenedChannels();
		void destoryChannel(System::String^channelId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);
		void getAuthorizedMediaUrl(int mediaType, String^mediaPath, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele);


		static const std::string ConvertStr(System::String^ str);
		static System::String^ ConvertStr(const std::string *stdStr);
		static System::String^ ConvertStr(const std::string stdStr);
		static std::list<int> ConvertIntList(List<int>^ ls, bool defaultZero);
		static std::list<std::string> ConvertStringList(List<String^>^ ls);

	private:
		void onReceiveMessage(const std::string &messageList, bool hasMore);
		void onRecallMessage(const std::string &operatorId, int64_t messageUid);
		void onDeleteMessage(int64_t messageUid);
		void onMessageDelivered(const std::string &str);
		void onMessageReaded(const std::string &str);

		void onUserInfoUpdate(const std::string &strValue);
		void onGroupInfoUpdate(const std::string &strValue);
		void onGroupMemberUpdate(const std::string &strValue);
		void onContactUpdate(const std::string &strValue);
		void onChannelInfoUpdate(const std::string &strValue);

		static OnConnectionStatusListenerDelegate^ m_OnConnectionStatusListenerDelegate;
		static OnReceiveMessageDelegate^ m_OnReceiveMessageDelegate;
		static OnRecallMessageDelegate^ m_OnRecallMessageDelegate;
		static OnDeleteMessageDelegate^ m_OnDeleteMessageDelegate;
		static OnMessageDeliveredDelegate^ m_OnMessageDeliveredDelegate;
		static OnMessageReadedDelegate^ m_OnMessageReadedDelegate;

		static OnStringDelegate ^m_onUserInfoUpdateListener;
		static OnStringDelegate ^m_onChannelInfoUpdateListener;
		static OnStringDelegate ^m_onContactUpdateListener;
		static OnStringDelegate ^m_onGroupMemberUpdateListener;
		static OnStringDelegate ^m_onGroupInfoUpdateListener;
	};
}
