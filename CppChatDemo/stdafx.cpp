
// stdafx.cpp : source file that includes just the standard includes
// CppChatDemo.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



void PutLog(std::string logStr)
{
  PutLog(CString(logStr.c_str()));
}

void PutLog(CString logStr)
{
  SYSTEMTIME tmSys;
  GetLocalTime(&tmSys);

  CString sFileName;
  sFileName.Format(L"CppChatDemo(%4d-%02d-%02d).txt", tmSys.wYear, tmSys.wMonth, tmSys.wDay);

  CString logPath;
  logPath.Format(L"%s\\%s", L"C:\\Users\\Fv-Team\\Documents\\", sFileName.GetString());

  //»’÷æƒ⁄»›
  CString sDate;
  sDate.Format(L"%4d-%02d-%02d %02d:%02d:%02d:%06d", tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
  CString sOut;
  sOut.Format(L"[%s]:%s\r\n", sDate.GetString(), logStr.GetString());

  FILE *pFile = _wfopen(logPath.GetString(), L"a+");
  if (pFile)
  {
    fwprintf(pFile, L"%s", (LPCTSTR)sOut);
    fclose(pFile);
  }
}