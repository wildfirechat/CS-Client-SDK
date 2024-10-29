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
  bool OnLoginBtn(std::string userid, std::string usersig);//界面登录按钮的响应函数
  bool OnLogoutBtn();	//登出
  bool isLogined();

  std::string GetClientId();  // 获取设备id，野火im申请token需要

  // WFSendMessageCallback
  void onSuccess(int64_t messageUid, int64_t timestamp) override {};
  // 上传进度的回调，注意仅当媒体内容大于300K才会有回调
  void onPrepared(int messageId, int64_t timestamp) override {};
  void onProgress(int uploaded, int total) override {};
  void onUploaded(const std::string &remoteUrl) override {};
  void onFailure(int errorCode) override {};

private:
  CIMImpl* m_pIMImpl;
};