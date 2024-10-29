#pragma once

#include <string>
#include <list>
#include <map>

#ifdef _GSTARSOFT_CURL_
#define GHCURL_API __declspec(dllexport)
#else
#define GHCURL_API __declspec(dllimport)
#endif

// typedef int (* pProgress_Callback)(void *clientp,
// 	curl_off_t dltotal,
// 	curl_off_t dlnow,
// 	curl_off_t ultotal,
// 	curl_off_t ulnow);

typedef int(*pProgress_Callback)(void *clientp,
	double dltotal,
	double dlnow,
	double ultotal,
	double ulnow);

class GHCURL_API CHttpTool
{
public:
	CHttpTool();
	~CHttpTool();
public:
	//nCodePage=CP_ACP时,ASCII与UNICODE互转;nCodePage=CP_UTF8时,UTF8与UNICODE互转;
	static std::wstring s2ws(const char * str, UINT nCodePage);
	static std::string ws2s(const wchar_t * str, UINT nCodePage);
public:
	//宽字符版本接口
	int SendGetW(const std::wstring & strUrl, std::wstring & strResult, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::wstring strUserAgent = L"",
		std::wstring * pstrHeader = NULL);
	int SendPostW(const std::wstring & strUrl, const std::wstring & strParam, std::wstring & strResult, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::wstring strUserAgent = L"",
		std::wstring * pstrHeader = NULL);
	int SendMultipartFormPostW(const std::wstring & strUrl, const std::map<std::wstring, std::wstring> & reqParamList, std::wstring & strResult, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::wstring strUserAgent = L"",
		std::wstring * pstrHeader = NULL);

	int SendUploadFileW(const std::wstring & strUrl, const std::map<std::wstring, std::wstring> & reqParamList, std::wstring & strResult, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, void * pUTask = NULL, pProgress_Callback pProgCall = NULL, const std::wstring strUserAgent = L"",
		std::wstring * pstrHeader = NULL);

  int SendUploadFile_PutOssW(const std::wstring & strUrl,
    const std::map<std::wstring, std::wstring> & reqParamList,
    std::wstring & strResult,
    const std::list<std::wstring> & reqHeaderList,
    int nConnectTimeout = 10,
    int nTimeout = 10,
    void * pUTask = NULL,
    pProgress_Callback pProgCall = NULL,
    std::wstring * pstrHeader = NULL);

	int SendDownloadFileW(const std::wstring & strUrl, std::wstring & strFilePath, const std::list<std::wstring> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, void * pDTask = NULL, pProgress_Callback pProgCall = NULL, const std::wstring strUserAgent = L"",
		std::wstring * pstrHeader = NULL);
public:
	int SendGet(const std::string & strUrl, std::string & strResult, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::string strUserAgent = "", std::string * pstrHeader = NULL);
	int SendPost(const std::string & strUrl, const std::string & strParam, std::string & strResult, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::string strUserAgent = "", std::string * pstrHeader = NULL);
	int SendMultipartFormPost(const std::string & strUrl, const std::map<std::string, std::string> & reqParamList, std::string & strResult, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, const std::string strUserAgent = "", std::string * pstrHeader = NULL);

	int SendUploadFile(const std::string & strUrl, const std::map<std::wstring, std::wstring> & reqParamList, std::string & strResult, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, void * pUTask = NULL, pProgress_Callback pProgCall = NULL, const std::string strUserAgent = "",
		std::string * pstrHeader = NULL);

  int SendUploadFile_PutOss(const std::string & strUrl,
    const std::map<std::wstring, std::wstring> & reqParamList,
    std::string & strResult,
    const std::list<std::string> & reqHeaderList,
    int nConnectTimeout = 10,
    int nTimeout = 10,
    void * pUTask = NULL,
    pProgress_Callback pProgCall = NULL,
    std::string * pstrHeader = NULL);

	int SendUploadFile2(const std::string & strUrl, const std::map<std::wstring, std::wstring> & reqParamList, std::string & strResult, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, void * pUTask = NULL, pProgress_Callback pProgCall = NULL, const std::string strUserAgent = "",
		std::string * pstrHeader = NULL);
	int SendDownloadFile(const std::string & strUrl, std::wstring & strFilePath, const std::list<std::string> & reqHeaderList, int nConnectTimeout = 10, int nTimeout = 10, void * pDTask = NULL, pProgress_Callback pProgCall = NULL, const std::string strUserAgent = "",
		std::string * pstrHeader = NULL);

	std::string UrlEncode(const char * str, int nLen);
	std::string UrlDecode(const char * str, int inLen, int * outLen = NULL);
	std::wstring UrlEncodeW(const wchar_t * str);
	std::wstring UrlDecodeW(const wchar_t * str, int * outLen = NULL);

#if 0
private:
  static int __cdecl InitGlobal(long flags = CURL_GLOBAL_DEFAULT);
private:
  static void __cdecl CleanupGlobal();
private:
  static size_t read_callback(void* buffer, size_t size, size_t nmemb, void* userp);
  static size_t write_html_data(void* buffer, size_t size, size_t nmemb, void* userp);
  static size_t write_head_data(void* buffer, size_t size, size_t nmemb, void* userp);
  static size_t write_file_data(void *ptr, size_t size, size_t nmemb, void *stream);

  /*static int progress_callback(void *clientp,
    curl_off_t dltotal,
    curl_off_t dlnow,
    curl_off_t ultotal,
    curl_off_t ulnow);*/

  static void dump(const char *text, FILE *stream, unsigned char *ptr, size_t size, char nohex);
  static int my_trace(CURL *handle, curl_infotype type, char *data, size_t size, void *userp);
private:
  void InitEasy();
  void ResetEasy();
  int SetEasyUrl(const char * pUrl);
  int PerformEasy();
  void CleanupEasy();
private:
  int SetTimeout(int nSeconds = 10);
  int SetUserAgent(const char * pUserAgent);
  int SetHttpHeaders(curl_slist* headers);
  int SetConnectTimeout(int nSeconds = 10);
private:
  CURL * m_curl;
  static int m_nInit;
#endif
};