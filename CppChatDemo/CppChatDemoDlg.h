
// CppChatDemoDlg.h : header file
//

#pragma once
#include "ChatClient.h"
#include "afxwin.h"

using namespace WFCLib;

// CCppChatDemoDlg dialog
class CCppChatDemoDlg : public CDialogEx, public ConnectionStatusListener, public ReceiveMessageListener
{
// Construction
public:
	CCppChatDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPPCHATDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void onConnectionStatusChanged(ConnectionStatus status);
	virtual void onReceiveMessages(const std::list<Message> &messages, bool hasMore);
	virtual void onRecallMessage(const std::string &operatorId, int64_t messageUid);
	virtual void onDeleteMessage(int64_t messageUid);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedTest();
	CStatic m_log;
};
