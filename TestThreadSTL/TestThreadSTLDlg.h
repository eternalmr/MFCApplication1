
// TestThreadSTLDlg.h: 头文件
//

#pragma once
#include <thread>

// CTestThreadSTLDlg 对话框
class CTestThreadSTLDlg : public CDialogEx
{
// 构造
public:
	CTestThreadSTLDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTTHREADSTL_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();



private:
	std::thread *t1;

public:
	static void thread_fun(int x);
	void thread_fun2(int x);
	static bool pause_flag;
	afx_msg void OnBnClickedButton3();
};
