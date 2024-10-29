#include "stdafx.h"
#include "CGCurlHelper.h"
#include "httptool.h"

std::string ws2s(const CString& str, UINT codePage)
{
  const wchar_t* _Source = (LPCTSTR)str;
  size_t _Dsize = WideCharToMultiByte(codePage, 0, _Source, -1, NULL, 0, NULL, NULL);
  char *_Dest = new char[_Dsize];
  WideCharToMultiByte(codePage, 0, _Source, -1, _Dest, (int)_Dsize, NULL, NULL);
  std::string result = _Dest;
  delete[]_Dest;
  return result;
}

CString s2ws(const char* str, UINT codePage)
{
  const char* _Source = str;
  size_t _Dsize = MultiByteToWideChar(codePage, 0, _Source, -1, NULL, 0);
  wchar_t *_Dest = new wchar_t[_Dsize];
  MultiByteToWideChar(codePage, 0, _Source, -1, _Dest, (int)_Dsize);
  CString result = _Dest;
  delete[]_Dest;
  return result;
}

//CString decodeAesData(const CString &text, const CString &desKey)
//{
//  std::string stext = ws2s(text, CP_UTF8);
//  CGCurlHelper  coder64;
//  int nOutsize = 0;
//  std::string c_text = coder64.decodeEx(stext.c_str(), (int)stext.length(), nOutsize);
//  CGCurlHelper  desper;
//  std::string decrypt_text = desper.aes_decrypt(c_text, ws2s(desKey, CP_UTF8));
//  return s2ws(decrypt_text.c_str(), CP_UTF8);
//}

int CGCurlHelper::SendPostW(const std::wstring & strUrl, const std::wstring & strParam, std::wstring & strResponse, const std::list<std::wstring>& reqHeaderList, int nConnectTimeout, int nTimeout, const std::wstring strUserAgent, std::wstring * pstrHeader)
{
  int nRet = -1;
  CHttpTool http;
  nRet = http.SendPostW(strUrl, strParam, strResponse, reqHeaderList, nConnectTimeout, nTimeout, strUserAgent, pstrHeader);
  return nRet;
}

void CGCurlHelper::Clear()
{
  if (NULL != m_pFile)
  {
    m_pFile->Close();
    delete m_pFile;
    m_pFile = NULL;
  }

  if (NULL != m_pConnection)
  {
    m_pConnection->Close();
    delete m_pConnection;
    m_pConnection = NULL;
  }
}


bool _queryPageJsonByCurl(const CString & strURL, const CString & strParam, CString & strResponse)
{
  bool bRet = false;
  std::wstring strReqUrl = strURL;
  std::wstring strReqPara = strParam;
  std::wstring strResult;
  std::list<std::wstring> reqHeaderList;
  reqHeaderList.push_back(L"Accept: application/json, text/javascript, */*");
  reqHeaderList.push_back(L"Content-type: application/json;charset=UTF-8");

  std::wstring strUserAgent(L"");
  CGCurlHelper http;
  int nRet = http.SendPostW(strReqUrl, strReqPara, strResult, reqHeaderList, 10, 10, strUserAgent);
  if (0 == nRet)
  {
    strResponse = strResult.c_str();
    bRet = true;
  }

  return bRet;
}

CStringA GetReqData(const CString& szReqData)
{
  // 预算-缓冲区中多字节的长度    
  int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, szReqData, -1, NULL, 0, NULL, NULL);
  char * pAssii = (char*)malloc(sizeof(char)*ansiiLen);
  // 开始向缓冲区转换字节    
  WideCharToMultiByte(CP_UTF8, 0, szReqData, -1, pAssii, ansiiLen, NULL, NULL);
  CStringA szRet(pAssii);
  free(pAssii);
  return szRet;
}

CString GetResData(const CStringA& szResData)
{
  // 预算-缓冲区中宽字节的长度    
  int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, szResData, -1, NULL, 0);
  wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
  // 开始向缓冲区转换字节    
  MultiByteToWideChar(CP_UTF8, 0, szResData, -1, pUnicode, unicodeLen);
  CString szRet(pUnicode);
  free(pUnicode);
  return szRet;
}


std::wstring UrlDecodeW(const wchar_t * str, int * outLen)
{
  CHttpTool http;
  return http.UrlDecodeW(str, outLen);
}