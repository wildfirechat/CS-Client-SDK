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
  // �����ӿ�
public:
  // ����״̬����
  virtual void onConnectionStatusChanged(ConnectionStatus status);
  // ��Ϣ����
  virtual void onReceiveMessages(const std::list<Message> &messages, bool hasMore);
  virtual void onRecallMessage(const std::string &operatorId, int64_t messageUid) {};
  virtual void onDeleteMessage(int64_t messageUid) {};
  // �û���Ϣ�������
  virtual void onUserInfoUpdated(const std::list<UserInfo> &userInfos) {};
  // Ⱥ����Ϣ�������
  virtual void onGroupInfoUpdated(const std::list<GroupInfo> &groupInfos) {};
  // Ⱥ���Ա�������
  virtual void onGroupMemberUpdated(const std::string &groupId) {};
  // ��ϵ��״̬����
  virtual void onContactUpdated(const std::list<std::string> &friendUids) {};
  // ��������״̬�������
  virtual void onFriendRequestUpdated(const std::list<std::string> &newRequests);
  // �û����ü���
  virtual void onUserSettingUpdated() {};
  // Ƶ����Ϣ�������
  virtual void onChannelInfoUpdated(const std::list<ChannelInfo> &channelInfo) {};

  // ������Ϣ�ص�
  virtual void onSuccess(int64_t messageUid, int64_t timestamp) {};
  // �ϴ����ȵĻص���ע�����ý�����ݴ���300K�Ż��лص�
  virtual void onPrepared(int messageId, int64_t timestamp) {};
  virtual void onProgress(int uploaded, int total) {};
  virtual void onUploaded(const std::string &remoteUrl) {};
  virtual void onFailure(int errorCode) {};
};


namespace JSON_PARSE
{
  bool ParseLoginInfo(std::string rep, LoginInfo& info);
}