#include "stdafx.h"
#include "global_stu.h"

HWND g_hWnd;

bool LoginInfo::ParseJson(Json::Value & json_value_msgs)
{
  if (!json_value_msgs.isObject())
  {
    return false;
  }

  userId = json_value_msgs["userId"].asString();
  token = json_value_msgs["token"].asString();
  bRegister = json_value_msgs["register"].asBool();
  userName = json_value_msgs["userName"].asString();
  portrait = json_value_msgs["portrait"].asString();
  resetCode = json_value_msgs["resetCode"].asString();
  return true;
}

void SetImWndHwnd(HWND hwnd)
{
  g_hWnd = hwnd;
}

HWND GetImWndHwnd()
{
  return g_hWnd;
}

//UTF-8תUnicode 
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

//unicode תΪ ascii 
std::string WideByte2Acsi(std::wstring& wstrcode) {
  int asciisize = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, NULL, 0, NULL, NULL);
  if (asciisize == ERROR_NO_UNICODE_TRANSLATION)
  {
    throw std::exception("Invalid UTF-8 sequence.");
  }
  if (asciisize == 0)
  {
    throw std::exception("Error in conversion.");
  }
  std::vector<char> resultstring(asciisize);
  int convresult = ::WideCharToMultiByte(CP_OEMCP, 0, wstrcode.c_str(), -1, &resultstring[0], asciisize, NULL, NULL);
  if (convresult != asciisize)
  {
    throw std::exception("La falla!");
  }
  return std::string(&resultstring[0]);
}

void appendLog(LPCTSTR str, std::string str2)
{
  CString cstr(Utf82Unicode(str2).c_str());
  cstr = str + cstr;

  appendLog(cstr);
}

void appendLog(std::string str)
{
  CString cstr(Utf82Unicode(str).c_str());
  appendLog(cstr);
}

void appendLog(CString str)
{
  str += "\n";
  ::SendMessage(GetImWndHwnd(), UPDATE_LOG, (LPARAM)(LPCTSTR)str, 0);
}

void WFGeneralVoidCallback::onFailure(int errorCode)
{
  CString str;
  str.Format(L"onFailure errorCode %d", errorCode);
  appendLog(str);
}