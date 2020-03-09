#pragma once


// COneItem 对话框

class COneItem : public CDialogEx
{
	DECLARE_DYNAMIC(COneItem)

public:
	COneItem(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COneItem();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CEdit *p_Edit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTestbtn();

	CStatic m_text;
	CButton m_btn;
	CProgressCtrl m_ProgressCtrl;

	int id;
	CString m_name;
};
