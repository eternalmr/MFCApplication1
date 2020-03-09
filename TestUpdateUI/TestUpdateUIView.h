
// TestUpdateUIView.h: CTestUpdateUIView 类的接口
//

#pragma once


class CTestUpdateUIView : public CFormView
{
protected: // 仅从序列化创建
	CTestUpdateUIView() noexcept;
	DECLARE_DYNCREATE(CTestUpdateUIView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_TESTUPDATEUI_FORM };
#endif

// 特性
public:
	CTestUpdateUIDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CTestUpdateUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_text;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_progressBar;
};

#ifndef _DEBUG  // TestUpdateUIView.cpp 中的调试版本
inline CTestUpdateUIDoc* CTestUpdateUIView::GetDocument() const
   { return reinterpret_cast<CTestUpdateUIDoc*>(m_pDocument); }
#endif

