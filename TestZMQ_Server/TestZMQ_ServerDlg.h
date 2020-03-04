﻿
// TestZMQ_ServerDlg.h: 头文件
//

#pragma once
#pragma warning(disable:4996)

#include <string>
#include "zhelpers.hpp"



using std::string;

// CTestZMQServerDlg 对话框
class CTestZMQServerDlg : public CDialogEx
{
// 构造
public:
	CTestZMQServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTZMQ_SERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CString m_recMsg;
	CString m_sendMsg;

	zmq::context_t context;
	zmq::socket_t replyer;

	string reply;
};
