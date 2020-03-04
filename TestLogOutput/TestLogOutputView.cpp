
// TestLogOutputView.cpp: CTestLogOutputView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestLogOutput.h"
#endif

#include "TestLogOutputDoc.h"
#include "TestLogOutputView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestLogOutputView

IMPLEMENT_DYNCREATE(CTestLogOutputView, CFormView)

BEGIN_MESSAGE_MAP(CTestLogOutputView, CFormView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestLogOutputView 构造/析构

CTestLogOutputView::CTestLogOutputView() noexcept
	: CFormView(IDD_TESTLOGOUTPUT_FORM)
{
	// TODO: 在此处添加构造代码

}

CTestLogOutputView::~CTestLogOutputView()
{
}

void CTestLogOutputView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CTestLogOutputView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CTestLogOutputView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CTestLogOutputView 打印

BOOL CTestLogOutputView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestLogOutputView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestLogOutputView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CTestLogOutputView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 在此处添加自定义打印代码
}


// CTestLogOutputView 诊断

#ifdef _DEBUG
void CTestLogOutputView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTestLogOutputView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTestLogOutputDoc* CTestLogOutputView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestLogOutputDoc)));
	return (CTestLogOutputDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestLogOutputView 消息处理程序
