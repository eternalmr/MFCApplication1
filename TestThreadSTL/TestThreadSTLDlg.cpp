
// TestThreadSTLDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestThreadSTL.h"
#include "TestThreadSTLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool CTestThreadSTLDlg::pause_flag = false;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestThreadSTLDlg 对话框



CTestThreadSTLDlg::CTestThreadSTLDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTTHREADSTL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestThreadSTLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestThreadSTLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestThreadSTLDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestThreadSTLDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestThreadSTLDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestThreadSTLDlg 消息处理程序

BOOL CTestThreadSTLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestThreadSTLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestThreadSTLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestThreadSTLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestThreadSTLDlg::thread_fun(int x)
{
	AfxMessageBox(TEXT("线程启动成功"));

	int num = x;
	CString str;

	while (true)
	{
		if (pause_flag)
		{
			std::this_thread::yield();
			continue;
		}
		str.Format(TEXT("num = %d\n"), num++);
		OutputDebugString(str);
		Sleep(1000);
	}

}

void CTestThreadSTLDlg::thread_fun2(int x)
{
	AfxMessageBox(TEXT("线程启动成功"));

	int num = x;
	CString str;

	while (true)
	{
		if (pause_flag)
		{
			std::this_thread::yield();
			continue;
		}
		str.Format(TEXT("num = %d\n"), num++);
		OutputDebugString(str);
		Sleep(1000);
	}
}

void CTestThreadSTLDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//CTestThreadSTLDlg dlg;

	//t1 = new std::thread(CTestThreadSTLDlg::thread_fun,0);
	//t1->detach();

	t1 = new std::thread(&CTestThreadSTLDlg::thread_fun2, this, 0);
	t1->detach();

}


void CTestThreadSTLDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(TEXT("暂停"));
	pause_flag = true;
}


void CTestThreadSTLDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(TEXT("继续"));
	pause_flag = false;
}
