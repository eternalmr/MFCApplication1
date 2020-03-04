
// TestThreadDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestThread.h"
#include "TestThreadDlg.h"
#include "afxdialogex.h"

#include <thread>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CTestThreadDlg 对话框



CTestThreadDlg::CTestThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestThreadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestThreadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestThreadDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestThreadDlg 消息处理程序

BOOL CTestThreadDlg::OnInitDialog()
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

void CTestThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestThreadDlg::OnPaint()
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
HCURSOR CTestThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//DWORD WINAPI ThreadProc(LPVOID lpParameter)
UINT __cdecl CTestThreadDlg::ThreadProc(LPVOID lpParameter)
{
	AfxMessageBox(TEXT("线程已启动"));
	CTestThreadDlg *pThreadDlg = (CTestThreadDlg *)lpParameter;
	CString msg;
	int num = pThreadDlg->m_num;
	while (true)
	{
		msg.Format(TEXT("num = %d"), num);
		OutputDebugString(msg);
		num++;
		Sleep(500);
	}
	return 0;
}

void __cdecl ThreadProc1(void* lpParameter)
{
	CString msg;
	msg.Format(TEXT("%d"), (int)lpParameter);
	AfxMessageBox(msg);
}

unsigned __stdcall ThreadProc2(void* lpParameter)
{
	CString msg;
	msg.Format(TEXT("%d"), (int)lpParameter);
	AfxMessageBox(msg);
	return 0;
}

HANDLE hThead = NULL;
void CTestThreadDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 第一种方法：CreateThread(win32程序中推荐)
	//DWORD dwThreadID = 1217;
	//HANDLE handle = CreateThread(NULL, 0, ThreadProc, (LPVOID)123, 0, &dwThreadID);
	//CloseHandle(handle);

	// 第二种方法：AfxBeginThread（MFC中推荐）
	m_num = 0;
	CWinThread* pThread =  AfxBeginThread(ThreadProc, this);
	hThead = pThread->m_hThread;

	// 第三种方法：_beginthread & _beginthreadex（标准c/c++中推荐）
	//_beginthread(ThreadProc1, 0, (void*)123);
	//_beginthreadex(NULL,0,ThreadProc2,(void*)123,0,NULL);

}




void CTestThreadDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SuspendThread(hThead);
}


void CTestThreadDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ResumeThread(hThead);
}
