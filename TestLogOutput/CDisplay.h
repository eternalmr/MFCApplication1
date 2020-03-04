#pragma once
#include "CTLog.h"
#include <thread>

// CDisplay 窗体视图

class CDisplay : public CFormView
{
	DECLARE_DYNCREATE(CDisplay)

protected:
	CDisplay();           // 动态创建所使用的受保护的构造函数
	virtual ~CDisplay();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DISPLAY };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();

	CTLog m_log;
	std::thread log_thread;
};


