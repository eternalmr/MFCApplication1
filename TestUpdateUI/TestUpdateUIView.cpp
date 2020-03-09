
// TestUpdateUIView.cpp: CTestUpdateUIView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestUpdateUI.h"
#endif

#include "TestUpdateUIDoc.h"
#include "TestUpdateUIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestUpdateUIView

IMPLEMENT_DYNCREATE(CTestUpdateUIView, CFormView)

BEGIN_MESSAGE_MAP(CTestUpdateUIView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestUpdateUIView::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTestUpdateUIView 构造/析构

CTestUpdateUIView::CTestUpdateUIView() noexcept
	: CFormView(IDD_TESTUPDATEUI_FORM)
{
	// TODO: 在此处添加构造代码

}

CTestUpdateUIView::~CTestUpdateUIView()
{

}

void CTestUpdateUIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, GetDocument()->myInt->num_);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressBar);
}

BOOL CTestUpdateUIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CTestUpdateUIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_progressBar.SetRange(0, 100);
	m_progressBar.SetStep(1);
	m_progressBar.SetPos(0);
}


// CTestUpdateUIView 诊断

#ifdef _DEBUG
void CTestUpdateUIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestUpdateUIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestUpdateUIDoc* CTestUpdateUIView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestUpdateUIDoc)));
	return (CTestUpdateUIDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestUpdateUIView 消息处理程序


void CTestUpdateUIView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CString csTmp;

	MyInt &myInt = MyInt::GetInstance();

	myInt.MyThread = std::thread(&MyInt::addNum, &myInt);
	myInt.MyThread.detach();
	SetTimer(1, 1000, NULL);
	
}

void CTestUpdateUIView::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case 1:
		//Sleep(2000);
		//tmp += 1;
		//m_value.Format(_T("%d"), tmp);
		//UpdateData(FALSE);
		//GetDocument()->UpdateAllViews(NULL);
		OnUpdate(NULL,0,NULL);
		break;
	case 2:
		//if (tmp1 >= 200)
		//{
		//	this->KillTimer(2);
		//	MessageBox(_T("定时器2停止！"), NULL, NULL);
		//	return;
		//}
		//Sleep(20);
		//tmp1 += 1;
		//m_value2.Format(_T("%d"), tmp1);
		//UpdateData(FALSE);
	default:
		break;
	}

	CFormView::OnTimer(nIDEvent);
}
