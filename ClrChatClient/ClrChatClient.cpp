// This is the main DLL file.

#include "stdafx.h"
#include <string>
#include "ClrChatClient.h"
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Text;

namespace ClrChatClient {

	//UTF-8转Unicode 
	std::wstring Utf82Unicode(const std::string& utf8string)
	{
		int widesize = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, NULL, 0);
		if (widesize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (widesize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<wchar_t> resultstring(widesize);
		int convresult = ::MultiByteToWideChar(CP_UTF8, 0, utf8string.c_str(), -1, &resultstring[0], widesize);
		if (convresult != widesize)
		{
			throw std::exception("La falla!");
		}
		return std::wstring(&resultstring[0]);
	}

	//unicode 转为 ascii 
	std::string WideByte2Acsi(std::wstring& wstrcode) {
		int asciisize = ::WideCharToMultiByte(CP_UTF8, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
		if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
		{
			throw std::exception("Invalid UTF-8 sequence.");
		}
		if (asciisize == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(asciisize);
		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
		if (convresult != asciisize)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}

	/**
	事件回调，一般都是一次性的。
	*/
	private class CallbackWrapper {
	public:
		CallbackWrapper(onGeneralVoidSuccessCallbackDelegate^ voidCB, onErrorCallbackDelegate^ errCB) {
			if (voidCB) {
				vscHandler = GCHandle::Alloc(voidCB);
				voidSuccessCB = Marshal::GetFunctionPointerForDelegate(voidCB);
			}

			if (errCB)
			{
				erHandler = GCHandle::Alloc(errCB);
				errorCB = Marshal::GetFunctionPointerForDelegate(errCB);
			}
		}
		CallbackWrapper(onGeneralStringSuccessCallbackDelegate^ stringCB, onErrorCallbackDelegate^ errCB) {
			if (stringCB)
			{
				sscHandler = GCHandle::Alloc(stringCB);
				stringSuccessCB = Marshal::GetFunctionPointerForDelegate(stringCB);
			}

			if (errCB)
			{
				erHandler = GCHandle::Alloc(errCB);
				errorCB = Marshal::GetFunctionPointerForDelegate(errCB);
			}
		}

		virtual ~CallbackWrapper()
		{
			if (vscHandler.IsAllocated)
			{
				vscHandler.Free();
			}
			if (sscHandler.IsAllocated)
			{
				sscHandler.Free();
			}
			if (erHandler.IsAllocated)
			{
				erHandler.Free();
			}
		}
		IntPtr voidSuccessCB;
		IntPtr stringSuccessCB;
		IntPtr errorCB;

		GCHandle sscHandler;
		GCHandle vscHandler;
		GCHandle erHandler;
	};

	private class SendMessageCallbackWrapper {
	public:
		SendMessageCallbackWrapper(onBigIntBigIntCallbackDelegate^ succCB, onIntIntCallbackDelegate^ proCb, onErrorCallbackDelegate^ errCB) {
			if (succCB) {
				scHandler = GCHandle::Alloc(succCB);
				successCB = Marshal::GetFunctionPointerForDelegate(succCB);
			}

			if (proCb)
			{
				pgHandler = GCHandle::Alloc(proCb);
				progressCB = Marshal::GetFunctionPointerForDelegate(proCb);
			}

			if (errCB)
			{
				erHandler = GCHandle::Alloc(errCB);
				errorCB = Marshal::GetFunctionPointerForDelegate(errCB);
			}
		}
		
		IntPtr successCB;
		IntPtr progressCB;
		IntPtr errorCB;
		GCHandle scHandler;
		GCHandle pgHandler;
		GCHandle erHandler;
		
		virtual ~SendMessageCallbackWrapper() {
			if (scHandler.IsAllocated)
			{
				scHandler.Free();
			}
			if (pgHandler.IsAllocated)
			{
				pgHandler.Free();
			}
			if (erHandler.IsAllocated)
			{
				erHandler.Free();
			}
		}
	};

	private class UploadMediaCallbackWrapper {
	public:
		UploadMediaCallbackWrapper(onGeneralStringSuccessCallbackDelegate^ succCB, onIntIntCallbackDelegate^ proCb, onErrorCallbackDelegate^ errCB) {
			if (succCB) {
				scHandler = GCHandle::Alloc(succCB);
				successCB = Marshal::GetFunctionPointerForDelegate(succCB);
			}

			if (proCb)
			{
				pgHandler = GCHandle::Alloc(proCb);
				progressCB = Marshal::GetFunctionPointerForDelegate(proCb);
			}

			if (errCB)
			{
				erHandler = GCHandle::Alloc(errCB);
				errorCB = Marshal::GetFunctionPointerForDelegate(errCB);
			}
		}
		virtual ~UploadMediaCallbackWrapper() {
			if (scHandler.IsAllocated)
			{
				scHandler.Free();
			}
			if (pgHandler.IsAllocated)
			{
				pgHandler.Free();
			}
			if (erHandler.IsAllocated)
			{
				erHandler.Free();
			}
		}
		IntPtr successCB;
		IntPtr progressCB;
		IntPtr errorCB;
		GCHandle scHandler;
		GCHandle pgHandler;
		GCHandle erHandler;
	};

	static void client_genernal_void_success_callback(void *pObj) {
		CallbackWrapper *callback = (CallbackWrapper *)pObj;
		((onGeneralVoidSuccessCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->voidSuccessCB, onGeneralVoidSuccessCallbackDelegate::typeid))();
		delete callback;
	}

	static void client_genernal_error_callback(void *pObj, int errorCode) {
		CallbackWrapper *callback = (CallbackWrapper *)pObj;
		((onErrorCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->voidSuccessCB, onErrorCallbackDelegate::typeid))(errorCode);
		delete callback;
	}

	static void client_genernal_string_success_callback(void *pObj, const std::string &value) {
		CallbackWrapper *callback = (CallbackWrapper *)pObj;
		((onGeneralStringSuccessCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->voidSuccessCB, onGeneralStringSuccessCallbackDelegate::typeid))(Proto::ConvertStr(value));
		delete callback;
	}


	static void client_sendMessage_success_callback(void *pObject, int64_t messageUid, int64_t timestamp) {
		if (pObject) {
			SendMessageCallbackWrapper *callback = (SendMessageCallbackWrapper *)pObject;
			((onBigIntBigIntCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->successCB, onBigIntBigIntCallbackDelegate::typeid))(messageUid, timestamp);
			delete callback;
		}
	}

	static void client_sendMessage_progress_callback(void *pObject, int uploaded, int total) {
		if (pObject) {
			SendMessageCallbackWrapper *callback = (SendMessageCallbackWrapper *)pObject;
			((onIntIntCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->progressCB, onIntIntCallbackDelegate::typeid))(uploaded, total);
		}
	}

	static void client_sendMessage_error_callback(void *pObject, int errorCode) {
		if (pObject) {
			SendMessageCallbackWrapper *callback = (SendMessageCallbackWrapper *)pObject;
			((onErrorCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->errorCB, onErrorCallbackDelegate::typeid))(errorCode);
			delete callback;
		}
	}

	static void client_uploadMedia_success_callback(void *pObject, const std::string &remoteUrl) {
		if (pObject) {
			UploadMediaCallbackWrapper *callback = (UploadMediaCallbackWrapper *)pObject;
			((onGeneralStringSuccessCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->successCB, onGeneralStringSuccessCallbackDelegate::typeid))(Proto::ConvertStr(remoteUrl));
			delete callback;
		}
	}

	static void client_uploadMedia_progress_callback(void *pObject, int uploaded, int total) {
		if (pObject) {
			UploadMediaCallbackWrapper *callback = (UploadMediaCallbackWrapper *)pObject;
			((onIntIntCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->progressCB, onIntIntCallbackDelegate::typeid))(uploaded, total);
		}
	}

	static void client_uploadMedia_error_callback(void *pObject, int errorCode) {
		if (pObject) {
			UploadMediaCallbackWrapper *callback = (UploadMediaCallbackWrapper *)pObject;
			((onErrorCallbackDelegate^)Marshal::GetDelegateForFunctionPointer(callback->errorCB, onErrorCallbackDelegate::typeid))(errorCode);
			delete callback;
		}
	}

	void Proto::setConversationTop(int type, String^ target, int line, bool top, onGeneralVoidSuccessCallbackDelegate^ successCB, onErrorCallbackDelegate^ errorCB) {
		WFClient::setConversationTop(type, ConvertStr(target), line, top, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(successCB, errorCB));
	}
	void Proto::setConversationSilent(int type, String^ target, int line, bool silent, onGeneralVoidSuccessCallbackDelegate^ successCB, onErrorCallbackDelegate^ errorCB) {
		WFClient::setConversationSlient(type, ConvertStr(target), line, silent, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(successCB, errorCB));
	}

	void Proto::setConversationDraft(int type, String^ target, int line, String^ draft) {
		WFClient::setConversationDraft(type, ConvertStr(target), line, ConvertStr(draft));
	}

	String^ Proto::getUnreadCount(List<int>^ types, List<int>^ lines) {
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

		return ConvertStr(WFClient::getUnreadCount(ts, ls));
	}

	String^ Proto::getUnreadCount(int type, String^ target, int line) {
		return ConvertStr(WFClient::getConversationUnreadCount(type, ConvertStr(target), line));
	}

	void Proto::clearUnreadStatus(int type, String^ target, int line) {
		WFClient::clearUnreadStatus(type, ConvertStr(target), line);
	}

	void Proto::clearUnreadStatus(List<int>^ conversationTypes, List<int>^ lines) {
		std::list<int> ts;
		for each (int type in conversationTypes)
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

		WFClient::clearUnreadStatus(ts, ls);
	}

	void Proto::clearAllUnreadStatus() {
		WFClient::clearAllUnreadStatus();
	}

	void Proto::setMediaMessagePlayed(long messageId) {
		WFClient::setMediaMessagePlayed(messageId);
	}

	String^ Proto::getMessages(int type, String^ target, int line, List<int>^ contentTypes, Int64 fromIndex, int count, String^ user) {
		std::list<int> cs;
		for each (int type in contentTypes)
		{
			cs.push_back(type);
		}
		bool direction = false;
		if (count < 0)
		{
			count = -count;
			direction = true;
		}
		return ConvertStr(WFClient::getMessages(type, ConvertStr(target), line, cs, fromIndex, direction, count, ConvertStr(user)));
	}
	
	String^ Proto::getMessages(List<int>^ conversationTypes, List<int>^ lines, List<int>^ contentTypes, Int64 fromIndex, int count, String^ user) {
		std::list<int> ts;
		for each (int type in conversationTypes)
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
		std::list<int> cs;
		for each (int type in contentTypes)
		{
			cs.push_back(type);
		}
		bool direction = false;
		if (count < 0)
		{
			count = -count;
			direction = true;
		}
		return ConvertStr(WFClient::getMessages(ts, ls, cs, fromIndex, direction, count, ConvertStr(user)));
	}

	String^ Proto::getMessages(List<int>^ conversationTypes, List<int>^ lines, int messageStatus, Int64 fromIndex, int count, String^ user) {
		std::list<int> ts;
		for each (int type in conversationTypes)
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
		
		bool direction = false;
		if (count < 0)
		{
			count = -count;
			direction = true;
		}

		return ConvertStr(WFClient::getMessages(ts, ls, messageStatus, fromIndex, direction, count, ConvertStr(user)));
	}
	
	void Proto::getRemoteMessages(int type, String^ target, int line, Int64 beforeMessageUid, int count, onGeneralStringSuccessCallbackDelegate^ strCB, onErrorCallbackDelegate^ errCB) {
		WFClient::getRemoteMessages(type, ConvertStr(target), line, beforeMessageUid, count, client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(strCB, errCB));
	}

	String^ Proto::getMessage(long messageId) {
		return ConvertStr(WFClient::getMessage(messageId));
	}

	String^ Proto::getMessageByUid(Int64 messageUid) {
		return ConvertStr(WFClient::getMessageByUid(messageUid));
	}

	String^ Proto::searchMessage(int type, String^ target, int line, String^ keyword, int count) {
		return ConvertStr(WFClient::searchMessage(type, ConvertStr(target), line, ConvertStr(keyword), count));
	}

	String^ Proto::sendMessage(int type, String^ target, int line, String^ content, List<String^>^ toUsers, int expireDuration, onBigIntBigIntCallbackDelegate^ succDele, onIntIntCallbackDelegate^ progressDele, onErrorCallbackDelegate^ errDele){
		std::list<std::string> us;
		if(toUsers) {
			for each (String^ user in toUsers)
			{
				us.push_back(ConvertStr(user));
			}
		}
		
		return ConvertStr(WFClient::sendMessage(type, ConvertStr(target), line, ConvertStr(content), us, expireDuration, client_sendMessage_success_callback, client_sendMessage_error_callback, client_sendMessage_progress_callback, new SendMessageCallbackWrapper(succDele, progressDele, errDele)));
	}

	void Proto::recallMessage(Int64 messageUid, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::recallMessage(messageUid, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::uploadMedia(String^ fileName, String^ mediaData, int mediaType, onGeneralStringSuccessCallbackDelegate^ succDele, onIntIntCallbackDelegate^ progressDele, onErrorCallbackDelegate^ errDele){
		std::string data = marshal_as<std::string>(mediaData);
		WFClient::uploadMedia(ConvertStr(fileName), data.c_str(), data.length(), mediaType, client_uploadMedia_success_callback, client_uploadMedia_error_callback, client_uploadMedia_progress_callback, new UploadMediaCallbackWrapper(succDele, progressDele, errDele));
	}

	bool Proto::deleteMessage(long messageId){
		return WFClient::deleteMessage(messageId);
	}

	void Proto::clearMessages(int type, String^ target, int line){ 
		WFClient::clearMessages(type, ConvertStr(target), line);
	}

	void Proto::clearMessages(int type, String^ target, int line, Int64 before){ 
		WFClient::clearMessages(type, ConvertStr(target), line, before);
	}

	String^ Proto::insert(int type, String^ target, int line, String^sender, String^ content, int status, bool notify, Int64 serverTime){
		return ConvertStr(WFClient::insertMessage(type, ConvertStr(target), line, ConvertStr(sender), ConvertStr(content), status, notify, serverTime));
	}

	void Proto::updateMessage(long messageId, String^ content){
		WFClient::updateMessage(messageId, ConvertStr(content));
	}

	String^ Proto::getUserInfo(String^userId, bool refresh){ 
		return ConvertStr(WFClient::getUserInfo(ConvertStr(userId), refresh, ""));
	}

	String^ Proto::getUserInfo(String^ userId, String^ groupId, bool refresh){
		return ConvertStr(WFClient::getUserInfo(ConvertStr(userId), refresh, ConvertStr(groupId)));
	}

	String^ Proto::getUserInfos(List<String^>^ userIds, String^ groupId){ 
		return ConvertStr(WFClient::getUserInfos(ConvertStringList(userIds), ConvertStr(groupId)));
	}

	void Proto::searchUser(String^keyword, int searchType, int page, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::searchUser(ConvertStr(keyword), searchType, page, client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	bool Proto::isMyFriend(String^userId){ 
		return WFClient::isMyFriend(ConvertStr(userId));
	}

	String^ Proto::getMyFriendList(bool refresh) { 
		return ConvertStr(WFClient::getMyFriendList(refresh)); 
	}

	String^ Proto::searchFriends(String^keyword){ 
		return ConvertStr(WFClient::searchFriends(ConvertStr(keyword)));
	}

	String^ Proto::searchGroups(String^keyword){
		return ConvertStr(WFClient::searchGroups(ConvertStr(keyword)));
	}

	String^ Proto::getIncommingFriendRequest(){ 
		return ConvertStr(WFClient::getIncommingFriendRequest());
	}
	String^ Proto::getOutgoingFriendRequest(){ 
		return ConvertStr(WFClient::getOutgoingFriendRequest());
	}
	void Proto::loadFriendRequestFromRemote(){ 
		WFClient::loadFriendRequestFromRemote();
	}
	int Proto::getUnreadFriendRequestStatus(){
		return WFClient::getUnreadFriendRequestStatus();
	}
	void Proto::clearUnreadFriendRequestStatus(){ 
		WFClient::clearUnreadFriendRequestStatus();
	}
	void Proto::deleteFriend(String^userId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){
		WFClient::deleteFriend(ConvertStr(userId), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::sendFriendRequest(String^userId, String^reason, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::sendFriendRequest(ConvertStr(userId), ConvertStr(reason), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::handleFriendRequest(String^userId, bool isAccpet, String^ friendExtra, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::handleFriendRequest(ConvertStr(userId), isAccpet, ConvertStr(friendExtra), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getFriendAlias(String^userId){
		return ConvertStr(WFClient::getFriendAlias(ConvertStr(userId)));
	}

	void Proto::setFriendAlias(String^userId, String^alias, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setFriendAlias(ConvertStr(userId), ConvertStr(alias), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	bool Proto::isBlackListed(String^userId){
		return WFClient::isBlackListed(ConvertStr(userId));
	}

	String^ Proto::getBlackList(bool refresh){ 
		return ConvertStr(WFClient::getBlackList(refresh));
	}

	void Proto::setBlackList(String^userId, bool isBlackListed, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){
		WFClient::setBlackList(ConvertStr(userId), isBlackListed, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getGroupMembers(String^groupId, bool forceUpdate){
		return ConvertStr(WFClient::getGroupMembers(ConvertStr(groupId), forceUpdate));
	}

	String^ Proto::getGroupInfo(String^groupId, bool refresh){ 
		return ConvertStr(WFClient::getGroupInfo(ConvertStr(groupId), refresh));
	}

	String^ Proto::getGroupMember(String^groupId, String^memberId){ 
		return ConvertStr(WFClient::getGroupMember(ConvertStr(groupId), ConvertStr(memberId)));
	}

	void Proto::createGroup(String^groupId, String^groupName, String^groupPortrait, int type, List<String^>^ groupMembers, List<int>^ notifyLines, String^ notifyContent, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::createGroup(ConvertStr(groupId), type, ConvertStr(groupName), ConvertStr(groupPortrait), ConvertStringList(groupMembers), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::addMembers(List<String^>^ members, String^groupId, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::addMembers(ConvertStr(groupId), ConvertStringList(members), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::kickoffMembers(List<String^>^ members, String^groupId, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::kickoffMembers(ConvertStr(groupId), ConvertStringList(members), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::quitGroup(String^groupId, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::quitGroup(ConvertStr(groupId), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::dismissGroup(String^groupId, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::dismissGroup(ConvertStr(groupId), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::modifyGroupInfo(String^groupId, int type, String^newValue, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::modifyGroupInfo(ConvertStr(groupId), type, ConvertStr(newValue), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::modifyGroupAlias(String^groupId, String^newAlias, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::modifyGroupAlias(ConvertStr(groupId), ConvertStr(newAlias), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::transferGroup(String^groupId, String^newOwner, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::transferGroup(ConvertStr(groupId), ConvertStr(newOwner), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::setGroupManager(String^groupId, bool isSet, List<String^>^ memberIds, List<int>^ notifyLines, String^ notifyContent, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setGroupManager(ConvertStr(groupId), isSet, ConvertStringList(memberIds), ConvertIntList(notifyLines, false), ConvertStr(notifyContent), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getFavGroups(){ 
		return ConvertStr(WFClient::getFavGroups());
	}

	bool Proto::isFavGroup(String^groupId){ 
		return WFClient::isFavGroup(ConvertStr(groupId));
	}

	void Proto::setFavGroup(String^groupId, bool isFav, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setFavGroup(ConvertStr(groupId), isFav, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getUserSetting(int scope, String^key){
		return ConvertStr(WFClient::getUserSetting(scope, ConvertStr(key)));
	}

	String^ Proto::getUserSettings(int scope){
		return ConvertStr(WFClient::getUserSettings(scope));
	}

	void Proto::setUserSetting(int scope, String^key, String^value, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setUserSetting(scope, ConvertStr(key), ConvertStr(value), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::modifyMyInfo(Dictionary<int, String^>^ values, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		std::list<std::pair<int, std::string>> pairs;
		for each(KeyValuePair<int, String^>^ kv in values)
		{
			pairs.push_back(std::pair<int, std::string>(kv->Key, ConvertStr(kv->Value)));
		}
		WFClient::modifyMyInfo(pairs, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	bool Proto::isGlobalSlient(){
		return WFClient::isGlobalSlient();
	}
	void Proto::setGlobalSlient(bool slient, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){
		WFClient::setGlobalSlient(slient, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}
	bool Proto::isHiddenNotificationDetail(){
		return false;
	}
	void Proto::setHiddenNotificationDetail(bool hidden, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setHiddenNotificationDetail(hidden, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	};

	void Proto::setHiddenGroupMemberName(bool hidden, String^groupId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::setHiddenGroupMemberName(ConvertStr(groupId), hidden, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::joinChatroom(String^chatroomId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::joinChatroom(ConvertStr(chatroomId), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::quitChatroom(String^chatroomId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::quitChatroom(ConvertStr(chatroomId), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::getChatroomInfo(String^chatroomId, Int64 updateDt, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::getChatroomInfo(ConvertStr(chatroomId), updateDt, client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::getChatroomMemberInfo(String^chatroomId, int maxCount, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::getChatroomMemberInfo(ConvertStr(chatroomId), maxCount, client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::createChannel(String^channelName, String^channelPortrait, int status, String^desc, String^extra, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::createChannel(ConvertStr(channelName), ConvertStr(channelPortrait), status, ConvertStr(desc), ConvertStr(extra), client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getChannelInfo(String^channelId, bool refresh){
		return ConvertStr(WFClient::getChannelInfo(ConvertStr(channelId), refresh));
	}
	void Proto::modifyChannelInfo(String^channelId, int type, String^newValue, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::modifyChannelInfo(ConvertStr(channelId), type, ConvertStr(newValue), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::searchChannel(String^keyword, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::searchChannel(ConvertStr(keyword), client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	bool Proto::isListenedChannel(String^channelId){
		return WFClient::isListenedChannel(ConvertStr(channelId));
	}

	void Proto::listenChannel(String^channelId, bool isListen, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::listenChannel(ConvertStr(channelId), isListen, client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	String^ Proto::getMyChannels(){
		return ConvertStr(WFClient::getMyChannels());
	}

	String^ Proto::getListenedChannels(){ 
		return ConvertStr(WFClient::getListenedChannels());
	}

	void Proto::destoryChannel(String^channelId, onGeneralVoidSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele){ 
		WFClient::destoryChannel(ConvertStr(channelId), client_genernal_void_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	void Proto::getAuthorizedMediaUrl(int mediaType, String^mediaPath, onGeneralStringSuccessCallbackDelegate^ succDele, onErrorCallbackDelegate^ errDele) {
		WFClient::getAuthorizedMediaUrl(mediaType, ConvertStr(mediaPath), client_genernal_string_success_callback, client_genernal_error_callback, new CallbackWrapper(succDele, errDele));
	}

	const std::string Proto::ConvertStr(String^ str) {
		std::wstring unicodeStr = marshal_as<std::wstring>(str);
		std::string utf8Str = WideByte2Acsi(unicodeStr);
		return utf8Str;
	}

	String^ Proto::ConvertStr(const std::string *stdStr) {
		std::wstring unicodeStr = Utf82Unicode(*stdStr);
		String ^clrStr = gcnew String(unicodeStr.c_str());
		WFClient::releaseDllString(stdStr);
		return clrStr;
	}

	String^ Proto::ConvertStr(const std::string stdStr) {
		std::wstring unicodeStr = Utf82Unicode(stdStr);
		String ^clrStr = gcnew String(unicodeStr.c_str());
		return clrStr;
	}

	std::list<int> Proto::ConvertIntList(List<int>^ ls, bool defaultZero) {
		std::list<int> result;
		for each (int l in ls)
		{
			result.push_back(l);
		}
		if (defaultZero && result.empty())
		{
			result.push_back(0);
		}
		return result;
	}

	std::list<std::string> Proto::ConvertStringList(List<String^>^ ls) {
		std::list<std::string> result;
		for each (String^ s in ls)
		{
			result.push_back(ConvertStr(s));
		}
		return result;
	}

	void Proto::onReceiveMessage(const std::string &messageList, bool hasMore) {
		if (m_OnReceiveMessageDelegate) {
			m_OnReceiveMessageDelegate(ConvertStr(messageList), hasMore);
		}
	}

	void Proto::onRecallMessage(const std::string &operatorId, int64_t messageUid) {
		if (m_OnRecallMessageDelegate) {
			m_OnRecallMessageDelegate(messageUid);
		}
	}

	void Proto::onDeleteMessage(int64_t messageUid) {
		if (m_OnDeleteMessageDelegate) {
			m_OnDeleteMessageDelegate(messageUid);
		}
	}


	void Proto::onUserInfoUpdate(const std::string &strValue) {
		if (m_onUserInfoUpdateListener)
		{
			m_onUserInfoUpdateListener(ConvertStr(strValue));
		}
	}

	void Proto::onGroupInfoUpdate(const std::string &strValue) {
		if (m_onGroupInfoUpdateListener)
		{
			m_onGroupInfoUpdateListener(ConvertStr(strValue));
		}
	}

	void Proto::onGroupMemberUpdate(const std::string &strValue) {
		if (m_onGroupMemberUpdateListener)
		{
			m_onGroupMemberUpdateListener(ConvertStr(strValue));
		}
	}

	void Proto::onContactUpdate(const std::string &strValue) {
		if (m_onContactUpdateListener)
		{
			m_onContactUpdateListener(ConvertStr(strValue));
		}
	}

	void Proto::onChannelInfoUpdate(const std::string &strValue) {
		if (m_onChannelInfoUpdateListener)
		{
			m_onChannelInfoUpdateListener(ConvertStr(strValue));
		}
	}

};