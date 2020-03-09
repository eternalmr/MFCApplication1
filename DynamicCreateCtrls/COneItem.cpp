// COneItem.cpp: 实现文件
//

#include "pch.h"
#include "DynamicCreateCtrls.h"
#include "COneItem.h"
#include "afxdialogex.h"
#include "DynamicCreateCtrlsDlg.h"


// COneItem 对话框

IMPLEMENT_DYNAMIC(COneItem, CDialogEx)

COneItem::COneItem(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ITEM, pParent)
	, m_name(_T(""))
{

}

COneItem::~COneItem()
{
}

void COneItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_TEXT, m_text);
	DDX_Control(pDX, IDC_TEXT, m_text);
	DDX_Control(pDX, IDC_TESTBTN, m_btn);
	DDX_Control(pDX, IDC_PROGRESS2, m_ProgressCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_name);
}


BEGIN_MESSAGE_MAP(COneItem, CDialogEx)
	ON_BN_CLICKED(IDC_TESTBTN, &COneItem::OnBnClickedTestbtn)
END_MESSAGE_MAP()


// COneItem 消息处理程序


BOOL COneItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_ProgressCtrl.ShowWindow(FALSE);
	// TODO:  在此添加额外的初始化
	//CString m_staticCaption;
	//CRect rect, rect2;
	//GetClientRect(&rect);
	//GetWindowRect(&rect2);
	//ScreenToClient(&rect2);

	//int perWidth = rect.Width() / 4;
	//int perHeight = rect2.top / 4;

	//p_Edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, CRect(0, 0, perWidth, perHeight), this, EDIT_ID + 100);
	//m_staticCaption.Format(TEXT("测试1"));
	//p_Edit->SetWindowText(m_staticCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COneItem::OnBnClickedTestbtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	str.Format(TEXT("这是第%d个任务"),id);
	MessageBox(str);

	m_ProgressCtrl.ShowWindow(SW_SHOWNORMAL);

	m_ProgressCtrl.SetRange32(0, 10);
	m_ProgressCtrl.SetStep(1);

	for (int i = 0; i < 10 ; i++)
	{
		m_ProgressCtrl.StepIt();
		Sleep(1000);
	}
	m_ProgressCtrl.ShowWindow(FALSE);
}
