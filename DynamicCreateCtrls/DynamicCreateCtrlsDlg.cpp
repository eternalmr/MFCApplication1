
// DynamicCreateCtrlsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DynamicCreateCtrls.h"
#include "DynamicCreateCtrlsDlg.h"
#include "afxdialogex.h"
#include "COneItem.h"


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


// CDynamicCreateCtrlsDlg 对话框



CDynamicCreateCtrlsDlg::CDynamicCreateCtrlsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DYNAMICCREATECTRLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicCreateCtrlsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDynamicCreateCtrlsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()

	//ON_BN_CLICKED(IDCREATE, &CDynamicCreateCtrlsDlg::OnBnClickedCreate)
	ON_BN_CLICKED(IDCANCEL, &CDynamicCreateCtrlsDlg::OnBnClickedCancel)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CDynamicCreateCtrlsDlg 消息处理程序

BOOL CDynamicCreateCtrlsDlg::OnInitDialog()
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
	RECT rect;
	GetClientRect(&rect);
	SetScrollRange(SB_VERT, 0, rect.bottom - rect.top, TRUE);

	CString str;
	for (int i = 0; i < DLG_NUM ; i++)
	{
		dlg[i].Create(IDD_ITEM, this);
		dlg[i].MoveWindow(0, 100*i + 1*i, 500, 100);
		dlg[i].id = i;
		str.Format(TEXT("第%d个任务"), i);
		dlg[i].m_text.SetWindowTextW(str);
		//UpdateData(FALSE);
		dlg[i].ShowWindow(SW_SHOWNORMAL);
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDynamicCreateCtrlsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDynamicCreateCtrlsDlg::OnPaint()
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
HCURSOR CDynamicCreateCtrlsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDynamicCreateCtrlsDlg::OnBnClickedCreate()
{
	// TODO: 在此添加控件通知处理程序代码
	////CString m_staticCaption;
	//CRect rect, rect2;
	//GetClientRect(&rect);
	//GetDlgItem(IDOK)->GetWindowRect(&rect2);
	//ScreenToClient(&rect2);

	//int m_counts = 2;
	//int perWidth = rect.Width() / 4;
	//int perHeight = rect2.top / m_counts;
	//COneItem *p_item;
	//for (int i = 0; i < m_counts; i++) {
	//	p_item = new COneItem();
	//	p_item->Create(IDD_ITEM,this);
	//	if (p_item != NULL) {
	//		p_Items.Add((void*)p_item);
	//		//	delete p_MyStatic;			
	//	}
	//	p_item->ShowWindow(SW_SHOW);
	//}

}


//void CDynamicCreateCtrlsDlg::OnBnClickedCreate()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString m_staticCaption;
//	CRect rect, rect2;
//	GetClientRect(&rect);
//	GetDlgItem(IDOK)->GetWindowRect(&rect2);
//	ScreenToClient(&rect2);
//
//	int m_counts = 21;
//	int perWidth = rect.Width() / 4;
//	int perHeight = rect2.top / m_counts;
//	CStatic *p_MyStatic;
//	CEdit *p_MyEdit;
//	for (int i = 0; i < m_counts; i++) {
//		p_MyStatic = new CStatic();
//		p_MyEdit = new CEdit();
//		m_staticCaption.Format(TEXT("第%d台IP地址:"), i + 1);
//		if (i % 2 == 0) {
//			p_MyStatic->Create(m_staticCaption, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(0, i*perHeight + 5, perWidth, (i + 1)*perHeight + 5), this);
//			m_staticCaption.Format(TEXT("%d台IP"), i + 1);
//			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(perWidth, i*perHeight + 5, perWidth * 2, (i + 1)*perHeight + 5), this, EDIT_ID + i);
//			p_MyEdit->SetWindowText(m_staticCaption);
//			if (p_MyStatic != NULL) {
//				p_MyStatics.Add((void*)p_MyStatic);			
//				//	delete p_MyStatic;			
//			}
//
//			if (p_MyEdit != NULL) {
//				p_MyEdits.Add((void*)p_MyEdit);			
//				//	delete p_MyEdit;			
//			}
//		}
//		else {
//			p_MyStatic->Create(m_staticCaption, WS_CHILD | WS_VISIBLE | SS_CENTER, CRect(perWidth * 2, (i - 1)*perHeight + 5, perWidth * 3, i*perHeight + 5), this);
//			m_staticCaption.Format(TEXT("%d台IP"), i + 1);
//			p_MyEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(perWidth * 3, (i - 1)*perHeight + 5, perWidth * 4, i*perHeight + 5), this, EDIT_ID + i);
//			p_MyEdit->SetWindowText(m_staticCaption);
//			if (p_MyStatic != NULL) {
//				p_MyStatics.Add((void*)p_MyStatic);				
//				//delete p_MyStatic;			
//			}
//			if (p_MyEdit != NULL) {
//				p_MyEdits.Add((void*)p_MyEdit);			
//				//	delete p_MyEdit;			
//			}
//		}
//	}
//
//
//}


void CDynamicCreateCtrlsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = p_MyStatics.GetSize();
	for (int i = 0; i < n; i++) {
		CStatic* pStatic = (CStatic*)p_MyStatics.GetAt(i);//	pStatic->DestroyWindow();	
		CString str;
		str.Format(TEXT("pStatic = %p\r\n", pStatic));
		OutputDebugString(str);
		str.Format(TEXT("p_MyStatics[%d] = %p\r\n", i, p_MyStatics[i]));
		OutputDebugString(str);
		if (pStatic != NULL)
			delete pStatic;
		p_MyStatics[i] = NULL;
	}
	p_MyStatics.RemoveAll();

	n = p_MyEdits.GetSize();
	for (int i = 0; i < n; i++) {
		CEdit* pEdit = (CEdit*)p_MyEdits.GetAt(i);	//pEdit->DestroyWindow();	
		if (pEdit != NULL)
			delete pEdit;
		p_MyEdits[i] = NULL;
	}  p_MyEdits.RemoveAll();
	CDialogEx::OnClose();
}

void CDynamicCreateCtrlsDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO scrollInfo;
	GetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
	int ScrollStep = 10;
	switch (nSBCode)
	{
	case SB_LINEUP:
		scrollInfo.nPos -= 1;
		if (scrollInfo.nPos < scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, 1);
		break;
	case SB_LINEDOWN:
		scrollInfo.nPos += 1;
		if (scrollInfo.nPos > scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, -1);
		break;
	case SB_TOP:
		ScrollWindow(0, (scrollInfo.nPos - scrollInfo.nMin) * 1);
		scrollInfo.nPos = scrollInfo.nMin;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	case SB_BOTTOM: 
		ScrollWindow(0, -(scrollInfo.nMax - scrollInfo.nPos) * 1);
		scrollInfo.nPos = scrollInfo.nMax;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	case SB_PAGEUP:
		scrollInfo.nPos -= ScrollStep;
		if (scrollInfo.nPos < scrollInfo.nMin)
		{
			scrollInfo.nPos = scrollInfo.nMin;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, 1 * ScrollStep);
		break;
	case SB_PAGEDOWN:
		scrollInfo.nPos += ScrollStep;
		if (scrollInfo.nPos > scrollInfo.nMax)
		{
			scrollInfo.nPos = scrollInfo.nMax;
			break;
		}
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		ScrollWindow(0, -1 * ScrollStep);
		break;
	case SB_ENDSCROLL:
		break;
	case SB_THUMBPOSITION:
		break;
	case SB_THUMBTRACK: 
		CString str;
		str.Format(TEXT("nPos1:%d nPos1:%d/n", scrollInfo.nPos, nPos));
		OutputDebugString(str);
		ScrollWindow(0, (scrollInfo.nPos - nPos));
		scrollInfo.nPos = nPos;
		SetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);
		break;
	}
}

BOOL CDynamicCreateCtrlsDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// TODO: Add your message handler code here and/or call default 
	//SCROLLINFO scrollinfo;
	if (zDelta == 120)
	{
		OnVScroll(SB_PAGEUP, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}
	else if (zDelta == -120)
	{
		OnVScroll(SB_PAGEDOWN, GetScrollPos(SB_VERT), GetScrollBarCtrl(SB_VERT));
	}


	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
