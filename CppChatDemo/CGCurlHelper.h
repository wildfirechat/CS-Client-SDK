#pragma once
#include <string>
#include <list>
#include <map>
#include <afxinet.h>

#define  BUFFER_SIZE       1024

#define  NORMAL_CONNECT             INTERNET_FLAG_KEEP_CONNECTION
#define  SECURE_CONNECT             NORMAL_CONNECT | INTERNET_FLAG_SECURE
#define  NORMAL_REQUEST             INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE
#define  SECURE_REQUEST             NORMAL_REQUEST | INTERNET_FLAG_SECURE | \
                                    INTERNET_FLAG_IGNORE_CERT_CN_INVALID| \
                                    INTERNET_FLAG_IGNORE_CERT_DATE_INVALID 

// 操作成功
#define SUCCESS        0
// 操作失败
#define FAILURE        1
// 操作超时
#define OUTTIME        2

class CGCurlHelper
{
public:
  CGCurlHelper() { m_pSession = new CInternetSession(_T("Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)")); };
  ~CGCurlHelper() {
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

    if (NULL != m_pSession)
    {
      m_pSession->Close();
      delete m_pSession;
      m_pSession = NULL;
    }
  };

  int SendPostW(const std::wstring & strUrl, const std::wstring & strParam, std::wstring & strResponse, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::wstring strUserAgent = L"",
    std::wstring * pstrHeader = NULL);

  //std::string CGCurlHelper::decodeEx(const char* Data, int DataByte, int& OutByte)
  //{
  //  return CBase64Coder::getInstance()->decodeEx(Data, DataByte, OutByte);
  //}

  //std::string aes_decrypt(const std::string &ptext, const std::string &key, int mode = 0)
  //{
  //  return CCipherer::aes_decrypt(ptext, key, (CCipherer::CRYPTO_MODE)mode);
  //}

  //std::string CGCurlHelper::rsa_formatPublicKey(const std::string & key)
  //{
  //  return CCipherer::rsa_formatPublicKey(key);
  //}

  //std::string CGCurlHelper::rsa_publicDecrypt(const std::string & cipher_text, const std::string & pub_key)
  //{
  //  return CCipherer::rsa_publicDecrypt(cipher_text, pub_key);
  //}

  void Clear();

  CInternetSession * m_pSession;
  CHttpConnection *m_pConnection = NULL;
  CHttpFile *m_pFile = NULL;
};

std::wstring UrlDecodeW(const wchar_t * str, int * outLen);
bool _queryPageJsonByCurl(const CString & strURL, const CString & strParam, CString & strResponse);
CStringA GetReqData(const CString& szReqData);
CString GetResData(const CStringA& szResData);
CString decodeAesData(const CString &text, const CString &desKey);