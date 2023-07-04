
// CppChatDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CppChatDemo.h"
#include "CppChatDemoDlg.h"
#include "afxdialogex.h"
#include "ChatClient.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//UTF-8转Unicode 
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

//unicode 转为 ascii 
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


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCppChatDemoDlg dialog



CCppChatDemoDlg::CCppChatDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CPPCHATDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ChatClient::Instance()->setConnectionStatusListener(this);
	ChatClient::Instance()->setReceiveMessageListener(this);
}

void CCppChatDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG, m_log);
}

void CCppChatDemoDlg::onConnectionStatusChanged(ConnectionStatus status)
{
	if (status == kConnectionStatusConnected)
	{
		::SetWindowText(m_hWnd, _T("已連接"));
	}
	else if (status == kConnectionStatusConnecting) {
		::SetWindowText(m_hWnd, _T("連接中..."));
	}
	else if (status == kConnectionStatusReceiving) {
		::SetWindowText(m_hWnd, _T("同步中..."));
	}
	else {
		::SetWindowText(m_hWnd, _T("鏈接狀態有問題！！！！"));
	}
}

void CCppChatDemoDlg::onReceiveMessages(const std::list<Message> & messageLists, bool hasMore)
{
	if (m_log)
	{
		CString existLog;
		m_log.GetWindowTextW(existLog);

		for (std::list<Message>::const_iterator it = messageLists.begin(); it != messageLists.end(); ++it) {
			const Message &msg = *it;
			UserInfo sender = ChatClient::Instance()->getUserInfo(msg.from, false);
			std::string line = sender.displayName;
			line += ":";
			line += msg.content->digest();
			line += "\n";

			existLog = Utf82Unicode(line).c_str() + existLog;
		}

		
		m_log.SetWindowTextW(existLog);
	}
}

void CCppChatDemoDlg::onRecallMessage(const std::string & operatorId, int64_t messageUid)
{
}
void CCppChatDemoDlg::onDeleteMessage(int64_t messageUid)
{
}


BEGIN_MESSAGE_MAP(CCppChatDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCppChatDemoDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CCppChatDemoDlg::OnBnClickedTest)
END_MESSAGE_MAP()


// CCppChatDemoDlg message handlers

BOOL CCppChatDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCppChatDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCppChatDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCppChatDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCppChatDemoDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	std::string clientId = ChatClient::Instance()->getClientId();
	printf(clientId.c_str());
	const std::string userId = "MTL7N7XX";
	const std::string token = "DkxMG1Xmnb2SWKeXfBuhoumloUhDui0nK2QLX970mQMIuGRcBQkyKZya2u3oCZLRzhheChM4NPkah5H5wc6aI8vLpxDxGlHDRGG+dLIkDCc548GoQNfWjiAumFiEh2950WCXQ9cneoEw2NtH78a/zxtbnE7RLh2lsHJ+ee8R4PM=";
	bool isNewDB = ChatClient::Instance()->connect(userId, token);
}


void CCppChatDemoDlg::OnBnClickedTest()
{
	UserInfo userInfo = ChatClient::Instance()->getUserInfo("MTL7N7XX", false);
	std::cout << "start test" << std::endl;
}
