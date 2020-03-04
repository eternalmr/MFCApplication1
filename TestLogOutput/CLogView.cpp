// CLogView.cpp: 实现文件
//

#include "pch.h"
#include "TestLogOutput.h"
#include "CLogView.h"


// CLogView

IMPLEMENT_DYNCREATE(CLogView, CFormView)

CLogView::CLogView()
	: CFormView(IDD_LOG)
{

}

CLogView::~CLogView()
{

}

void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_showLog);
}


BEGIN_MESSAGE_MAP(CLogView, CFormView)
END_MESSAGE_MAP()


// CLogView 诊断

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLogView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CLogView 消息处理程序
void CLogView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_showLog.m_bRun = TRUE;
	showLog_thread = std::thread(&CTLogEdit::TLogEditThreadNew, &m_showLog);
	data_thread = std::thread(&CTLogEdit::TLogTestThread, &m_showLog);
	OutputDebugString(TEXT("启动日志读取线程"));
	// TODO: 在此添加专用代码和/或调用基类

}
