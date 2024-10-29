
// CppChatDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CppChatDemo.h"
#include "CppChatDemoDlg.h"
#include "afxdialogex.h"
#include "ChatClient.h"
#include "CGCurlHelper.h"
#include "CChatTools.h"
#include "WFire.h"
#include "message/TextMessageContent.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <vector>
#include <atlstr.h> // For CA2T


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
}

CCppChatDemoDlg::~CCppChatDemoDlg()
{
  CChatTools::GetInstance()->OnLogoutBtn();
}

void CCppChatDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG, m_log);
}

BEGIN_MESSAGE_MAP(CCppChatDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCppChatDemoDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CCppChatDemoDlg::OnBnClickedTest)
  ON_EN_CHANGE(IDC_EDIT1, &CCppChatDemoDlg::OnEnChangeEdit1)
  ON_MESSAGE(UPDATE_LOG, &CCppChatDemoDlg::OnUpdateLogMessage)
  ON_MESSAGE(WM_HANDLEMESSAGE, &CCppChatDemoDlg::OnHandleMessage)
  ON_BN_CLICKED(IDC_BUTTON3, &CCppChatDemoDlg::OnBnClickedButton3)
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
  SetImWndHwnd(GetSafeHwnd());
  GetDlgItem(IDC_EDIT1)->SetWindowText(L"18717313325");
  GetDlgItem(IDC_EDIT2)->SetWindowText(L"66666");

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
  LoginInfo info;
  GetLoginInfo(info);

  bool isNewDB = ChatClient::Instance()->connect(info.userId, info.token);
}


void CCppChatDemoDlg::OnBnClickedTest()
{
	UserInfo userInfo = ChatClient::Instance()->getUserInfo("MTL7N7XX", false);
	std::cout << "start test" << std::endl;
  test();
}


void CCppChatDemoDlg::OnEnChangeEdit1()
{
  // TODO:  如果该控件是 RICHEDIT 控件，它将不
  // 发送此通知，除非重写 __super::OnInitDialog()
  // 函数并调用 CRichEditCtrl().SetEventMask()，
  // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

  // TODO:  在此添加控件通知处理程序代码
}

LRESULT CCppChatDemoDlg::OnUpdateLogMessage(WPARAM wParam, LPARAM lParam)
{
  if (m_log)
  {
    CString existLog;
    m_log.GetWindowTextW(existLog);

    CString rmsg((LPCTSTR)wParam);
    existLog = rmsg + existLog;

    m_log.SetWindowTextW(existLog);
  }

  return 0;
}

LRESULT CCppChatDemoDlg::OnHandleMessage(WPARAM wParam, LPARAM lParam)
{
  eHandleType e = (eHandleType)wParam;
  switch ((eHandleType)wParam)
  {
  case eRequestConvList:
  {
    if (!CChatTools::GetInstance()->isLogined())
    {
      appendLog(L"未登录");
      return 0;
    }
  }
  break;
  default:
    break;
  }

  return 0;
}

void CCppChatDemoDlg::GetLoginInfo(LoginInfo & info)
{
  std::string clientId = ChatClient::Instance()->getClientId();

  // SDK初始化
  CChatTools::GetInstance()->Init(new WFire);

  // 请求userid token
  CString phone, superCode, json;
  GetDlgItem(IDC_EDIT1)->GetWindowText(phone);
  GetDlgItem(IDC_EDIT2)->GetWindowText(superCode);
  json.Format(L"{\"mobile\":\"%s\", \"code\":\"%s\", \"clientId\":\"%s\", \"platform\":\"3\"}", phone, superCode, CString(clientId.c_str()));

  CString strRep;
  _queryPageJsonByCurl(L"http://101.42.33.126:8888/login", json, strRep);

  JSON_PARSE::ParseLoginInfo(std::string(CT2A(strRep)), info);
}

void CCppChatDemoDlg::test()
{
  appendLog(L"开始测试");

  std::string userid = ChatClient::Instance()->getCurrentUserId();
  appendLog(L"当前用户userId为:", userid);

  UserInfo useInfo = ChatClient::Instance()->getUserInfo(userid, false);
  if (useInfo.uid.empty())
  {
    appendLog(L"当前登录用户信息为空，这可能是因为本地没有存储，协议栈会去服务器同步，同步后会通过用户信息更新回调来通知");
  }
  else 
  {
    appendLog(L"当前登录用户名：", useInfo.displayName);
  }

  int64_t deltaTime = ChatClient::Instance()->getServerDeltaTime();
  appendLog(L"当前设备与服务器之间的时间差为:", std::to_string(deltaTime));

  // 请求会话列表
  std::list<int> convType = { Single_Type, Group_Type, Channel_Type };
  std::list<int> lines = { 0 };
  std::list<ConversationInfo> convs = ChatClient::Instance()->getConversationInfos(convType, lines);
  CString log;
  log.Format(L"获取到 %d 条会话记录", convs.size());
  appendLog(log);

  // 创建会话
  Conversation conv;
  conv.conversationType = Single_Type;
  conv.target = "cgc8c8VB";
  ConversationInfo info = ChatClient::Instance()->getConversationInfo(conv);
  ChatClient::Instance()->setConversationTop(conv, true, WFGeneralVoidCallback::GetInstance());

  // 文字消息
  TextMessageContent text;
  text.content = "hello world2";
  text.extra = "123";

  std::string content = text.encode().toJson();
  ChatClient::Instance()->sendMessage(conv, text, std::list<std::string>(), 0, CChatTools::GetInstance());

  std::list<int> types = { Single_Type, Group_Type };
  std::list<int> contentTypes = { MESSAGE_CONTENT_TYPE_TEXT };
  std::list<Message> messages = ChatClient::Instance()->getMessages(types, lines, contentTypes, 0, 100, "");
  appendLog("get message count" + messages.size());
}

// 添加好友按钮
void CCppChatDemoDlg::OnBnClickedButton3()
{
  // 添加好友
  CString sUid;
  GetDlgItem(IDC_EDIT3)->GetWindowText(sUid);
  std::string targetUid = CT2A(sUid);
  ChatClient::Instance()->sendFriendRequest(targetUid, "friendReq", "plz", WFGeneralVoidCallback::GetInstance());
  appendLog(L"已发送好友请求：", targetUid);
}
