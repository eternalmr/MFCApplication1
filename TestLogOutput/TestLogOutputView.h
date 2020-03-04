
// TestLogOutputView.h: CTestLogOutputView 类的接口
//

#pragma once


class CTestLogOutputView : public CFormView
{
protected: // 仅从序列化创建
	CTestLogOutputView() noexcept;
	DECLARE_DYNCREATE(CTestLogOutputView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TESTLOGOUTPUT_FORM };
#endif

// 特性
public:
	CTestLogOutputDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTestLogOutputView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestLogOutputView.cpp 中的调试版本
inline CTestLogOutputDoc* CTestLogOutputView::GetDocument() const
   { return reinterpret_cast<CTestLogOutputDoc*>(m_pDocument); }
#endif

