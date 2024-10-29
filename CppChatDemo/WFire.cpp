#include "stdafx.h"
#include "WFire.h"
#include "json.h"

void WFire::Init()
{
  // 注册监听
  ChatClient::Instance()->setConnectionStatusListener(this);
  ChatClient::Instance()->setReceiveMessageListener(this);
  ChatClient::Instance()->setUserInfoUpdateListener(this);
  ChatClient::Instance()->setGroupInfoUpdateListener(this);
  ChatClient::Instance()->setGroupMemberUpdateListener(this);
  ChatClient::Instance()->setContactUpdateListener(this);
  ChatClient::Instance()->setFriendRequestUpdateListener(this);
  ChatClient::Instance()->setUserSettingUpdateListener(this);
  ChatClient::Instance()->setChannelInfoUpdateListener(this);
}

bool WFire::Login(std::string userid, std::string usersig)
{
  return ChatClient::Instance()->connect(userid, usersig);
}

bool WFire::Logout()
{
  return ChatClient::Instance()->disconnect();
}

bool WFire::isLogined()
{
  return ChatClient::Instance()->isLogined();
}

std::string WFire::GetClientId()
{
  return ChatClient::Instance()->getClientId();
}

void WFire::onConnectionStatusChanged(ConnectionStatus status)
{
  if (status == kConnectionStatusConnected)
  {
    ::SetWindowText(GetImWndHwnd(), _T("已連接"));

    // 获取最近会话列表
    ::PostMessage(GetImWndHwnd(), WM_HANDLEMESSAGE, eRequestConvList, 0);
  }
  else if (status == kConnectionStatusConnecting) {
    ::SetWindowText(GetImWndHwnd(), _T("連接中..."));
  }
  else if (status == kConnectionStatusReceiving) {
    ::SetWindowText(GetImWndHwnd(), _T("同步中..."));
  }
  else {
    ::SetWindowText(GetImWndHwnd(), _T("鏈接狀態有問題！！！！"));
  }
}

void WFire::onReceiveMessages(const std::list<Message>& messages, bool hasMore)
{
  for (std::list<Message>::const_iterator it = messages.begin(); it != messages.end(); ++it) {
    const Message &msg = *it;
    UserInfo sender = ChatClient::Instance()->getUserInfo(msg.from, false);
    std::string line = sender.displayName;
    line += ":";
    line += msg.content->digest();
    line += "\n";

    CString cstr(Utf82Unicode(line).c_str());
    ::SendMessage(GetImWndHwnd(), UPDATE_LOG, (LPARAM)(LPCTSTR)cstr, 0);
  }
}

void WFire::onFriendRequestUpdated(const std::list<std::string>& newRequests)
{
  std::list<std::string>::const_iterator it = newRequests.begin();
  for (; it != newRequests.end(); ++it)
  {
    const std::string str = *it;
    ChatClient::Instance()->handleFriendRequest(str, true, "", WFGeneralVoidCallback::GetInstance());

    CString log(Utf82Unicode(str).c_str());
    log += " accpet friend request\n";
    ::SendMessage(GetImWndHwnd(), UPDATE_LOG, (LPARAM)(LPCTSTR)log, 0);
  }
}

// 解析
bool JSON_PARSE::ParseLoginInfo(std::string rep, LoginInfo& info)
{
  try
  {
    Json::Value json_value_msgs;
    Json::Reader reader;
    if (!reader.parse(rep, json_value_msgs))
    {
      PutLog(std::string("获取登录信息 解析json失败:") + reader.getFormattedErrorMessages());
      return false;
    }

    if (json_value_msgs["code"].asInt() != 0)
      return false;

    info.ParseJson(json_value_msgs["result"]);
  }
  catch (...)
  {
    PutLog(L"获取登录信息 解析json发生异常:");
    return false;
  }

  PutLog(L"ParseLoginInfo exit!!!");
  return true;
}
