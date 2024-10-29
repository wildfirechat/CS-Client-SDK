#pragma once
#include "CIMImpl.h"
#include "ChatClient.h"

using namespace WFCLib;

class WFire :
  public CIMImpl,
  ConnectionStatusListener,
  ReceiveMessageListener,
  UserInfoUpdateListener,
  GroupInfoUpdateListener,
  GroupMemberUpdateListener,
  ContactUpdateListener,
  FriendRequestUpdateListener,
  UserSettingUpdateListener,
  ChannelInfoUpdateListener,
  WFSendMessageCallback
{
public:
  WFire() {}

  virtual void Init();
  virtual bool Login(std::string userid, std::string usersig);
  virtual bool Logout();
  virtual bool isLogined();
  virtual std::string GetClientId();
  // 监听接口
public:
  // 连接状态监听
  virtual void onConnectionStatusChanged(ConnectionStatus status);
  // 消息监听
  virtual void onReceiveMessages(const std::list<Message> &messages, bool hasMore);
  virtual void onRecallMessage(const std::string &operatorId, int64_t messageUid) {};
  virtual void onDeleteMessage(int64_t messageUid) {};
  // 用户信息变更监听
  virtual void onUserInfoUpdated(const std::list<UserInfo> &userInfos) {};
  // 群组信息变更监听
  virtual void onGroupInfoUpdated(const std::list<GroupInfo> &groupInfos) {};
  // 群组成员变更监听
  virtual void onGroupMemberUpdated(const std::string &groupId) {};
  // 联系人状态监听
  virtual void onContactUpdated(const std::list<std::string> &friendUids) {};
  // 好友请求状态变更监听
  virtual void onFriendRequestUpdated(const std::list<std::string> &newRequests);
  // 用户设置监听
  virtual void onUserSettingUpdated() {};
  // 频道信息变更监听
  virtual void onChannelInfoUpdated(const std::list<ChannelInfo> &channelInfo) {};

  // 发送消息回调
  virtual void onSuccess(int64_t messageUid, int64_t timestamp) {};
  // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
  virtual void onPrepared(int messageId, int64_t timestamp) {};
  virtual void onProgress(int uploaded, int total) {};
  virtual void onUploaded(const std::string &remoteUrl) {};
  virtual void onFailure(int errorCode) {};
};


namespace JSON_PARSE
{
  bool ParseLoginInfo(std::string rep, LoginInfo& info);
}