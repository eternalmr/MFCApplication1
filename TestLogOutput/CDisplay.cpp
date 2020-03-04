// CDisplay.cpp: 实现文件
//

#include "pch.h"
#include "TestLogOutput.h"
#include "CDisplay.h"
#include <thread>
#include "CLogView.h"
#include "CTLog.h"
#include "CTLogEdit.h"

//InitializeCriticalSection(&CTLogEdit::m_csTLogEditStatic);
CRITICAL_SECTION CTLogEdit::m_csTLogEditStatic;
CPtrList CTLogEdit::m_TLogItemQueStatic(10);
//InitializeCriticalSection(CTLogEdit::m_csTLogEditStatic);
// CDisplay

IMPLEMENT_DYNCREATE(CDisplay, CFormView)

CDisplay::CDisplay()
	: CFormView(IDD_DISPLAY),m_log()
{

}

CDisplay::~CDisplay()
{
}

void CDisplay::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDisplay, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDisplay::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CDisplay::OnBnClickedButton3)
END_MESSAGE_MAP()


// CDisplay 诊断

#ifdef _DEBUG
void CDisplay::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDisplay::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDisplay 消息处理程序
//void myfun(int num)
//{
//	//CTLog log;
//	CString str;
//	CTLogEdit log;
//	for (int i = 0; i < num ; i++){
//		str.Format(TEXT("num = %d\r\n"), i);
//		log.AddLine(TEXT("num = %d\r\n"), TLP_NORMAL);
//		OutputDebugString(str);
//		//log.TLogLine(str,TLP_NORMAL);
//		Sleep(500);
//	}
//}

void CDisplay::OnBnClickedButton1()
{
	CTLogEdit log;
	// TODO: 在此添加控件通知处理程序代码
	m_log.AddLine(TEXT("press button\r\n"));
	log.AddLine2(TEXT("press button\r\n"));
	MessageBox(TEXT("添加日志"));
}

void CDisplay::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_log.m_bRun = TRUE;
	log_thread = std::thread(&CTLog::TLogThreadNew, &m_log);
	MessageBox(TEXT("启动日志线程"));
}
