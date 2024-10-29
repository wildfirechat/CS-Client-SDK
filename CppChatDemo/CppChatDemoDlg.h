
// CppChatDemoDlg.h : header file
//

#pragma once
#include "ChatClient.h"
#include "afxwin.h"

using namespace WFCLib;

// CCppChatDemoDlg dialog
class CCppChatDemoDlg : public CDialogEx
{
// Construction
public:
	CCppChatDemoDlg(CWnd* pParent = NULL);	// standard constructor
  ~CCppChatDemoDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPPCHATDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
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
  afx_msg void OnEnChangeEdit1();
  afx_msg LRESULT OnUpdateLogMessage(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnHandleMessage(WPARAM wParam, LPARAM lParam);

  // «Î«Ûuserid token
  void GetLoginInfo(LoginInfo& info);

private:
  void test();
public:
  afx_msg void OnBnClickedButton3();
};
