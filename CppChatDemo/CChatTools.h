#pragma once
#include "ChatClient.h"
#include "CIMImpl.h"

class CChatTools : public WFCLib::WFSendMessageCallback
{
public:
  CChatTools() :m_pIMImpl(nullptr) {}
  virtual ~CChatTools() {}

  static CChatTools* GetInstance()
  {
    static CChatTools ins;
    return &ins;
  }

  void Init(CIMImpl *p);
  bool OnLoginBtn(std::string userid, std::string usersig);//�����¼��ť����Ӧ����
  bool OnLogoutBtn();	//�ǳ�
  bool isLogined();

  std::string GetClientId();  // ��ȡ�豸id��Ұ��im����token��Ҫ

  // WFSendMessageCallback
  void onSuccess(int64_t messageUid, int64_t timestamp) override {};
  // �ϴ����ȵĻص���ע�����ý�����ݴ���300K�Ż��лص�
  void onPrepared(int messageId, int64_t timestamp) override {};
  void onProgress(int uploaded, int total) override {};
  void onUploaded(const std::string &remoteUrl) override {};
  void onFailure(int errorCode) override {};

private:
  CIMImpl* m_pIMImpl;
};