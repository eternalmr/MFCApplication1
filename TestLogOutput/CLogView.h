﻿#pragma once

#include <thread>
#include "CTLogEdit.h"

// CLogView 窗体视图

class CLogView : public CFormView
{
	DECLARE_DYNCREATE(CLogView)

protected:

public:
	CLogView();           // 动态创建所使用的受保护的构造函数
	virtual ~CLogView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOG };
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
	CTLogEdit m_showLog;
	std::thread showLog_thread;
	std::thread data_thread;

public:
	virtual void OnInitialUpdate();
};


