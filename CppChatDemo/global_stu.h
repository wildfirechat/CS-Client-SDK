#pragma once
#include <string>
#include "json.h"
#include "ChatClient.h"

#define UPDATE_LOG WM_USER + 1
#define WM_HANDLEMESSAGE WM_USER + 2

extern HWND g_hWnd;
void SetImWndHwnd(HWND hwnd);
HWND GetImWndHwnd();

std::wstring Utf82Unicode(const std::string& utf8string);
std::string WideByte2Acsi(std::wstring& wstrcode);

struct LoginInfo
{
  std::string userId;
  std::string token;
  bool bRegister;
  std::string userName;
  std::string portrait;
  std::string resetCode;

  bool ParseJson(Json::Value& json_value_msgs);
};

/*
 通用的void的事件回调
 */
class WFGeneralVoidCallback : public WFCLib::GeneralVoidCallback
{
public:
  static WFGeneralVoidCallback* GetInstance()
  {
    static WFGeneralVoidCallback ins;
    return &ins;
  }

  WFGeneralVoidCallback() {};
  virtual ~WFGeneralVoidCallback() {};

  virtual void onSuccess() { ::SendMessage(GetImWndHwnd(), UPDATE_LOG, (LPARAM)L"onSuccess\n", 0); };
  virtual void onFailure(int errorCode);
};









// 
enum eHandleType
{
  eRequestConvList = 1  // 请求会话列表
};

void appendLog(LPCTSTR str, std::string str2);
void appendLog(std::string str);
void appendLog(CString str);