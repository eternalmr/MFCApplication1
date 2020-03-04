
// DynamicCreateCtrlsDlg.h: 头文件
//

#pragma once
#include "COneItem.h"

#define  DLG_NUM 5
#define  EDIT_ID 10000

// CDynamicCreateCtrlsDlg 对话框
class CDynamicCreateCtrlsDlg : public CDialogEx
{
// 构造
public:
	CDynamicCreateCtrlsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMICCREATECTRLS_DIALOG };
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

public:
	CPtrArray p_MyStatics;
	CPtrArray p_MyEdits;
	CPtrArray p_Items;

	COneItem dlg[DLG_NUM];

	afx_msg void OnBnClickedCreate();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
