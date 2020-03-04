// CTLogEdit.cpp: 实现文件
//

#include "pch.h"
#include "TestLogOutput.h"
#include "CTLogEdit.h"

COLORREF TLP_DEBUG_COLOR = RGB(0, 0, 0);   //black
COLORREF TLP_DETAIL_COLOR = RGB(0, 255, 0);  //green
COLORREF TLP_NORMAL_COLOR = RGB(0, 0, 255);  //blue
COLORREF TLP_ERROR_COLOR = RGB(255, 0, 0);   //red

// CTLogEdit

IMPLEMENT_DYNCREATE(CTLogEdit, CRichEditCtrl)

CTLogEdit::CTLogEdit() :
	m_bRun(FALSE),
	m_nLineLimit(30),
	m_bAutoScroll(TRUE)
{
	InitializeCriticalSection(&m_csTLogEdit);
	//BOOL m_bRun;
	//CRITICAL_SECTION m_csTLogEdit;
	//CPtrList m_TLogItemQue;
	//int m_nLineLimit;
	//BOOL m_bAutoScroll;
}

CTLogEdit::~CTLogEdit()
{

}

BEGIN_MESSAGE_MAP(CTLogEdit, CRichEditCtrl)
END_MESSAGE_MAP()


// CTLogEdit 诊断

#ifdef _DEBUG
void CTLogEdit::AssertValid() const
{
	CRichEditCtrl::AssertValid();
}

#ifndef _WIN32_WCE
void CTLogEdit::Dump(CDumpContext& dc) const
{
	CRichEditCtrl::Dump(dc);
}

void CTLogEdit::SetLogLineColor(long lPos, TLOGPRIORITY tlp)
{
	SetSel(lPos, lPos);
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof(CHARFORMAT2));
	cf.dwMask |= CFM_COLOR;
	cf.dwEffects &= ~CFE_AUTOCOLOR;
	switch (tlp)
	{
	case TLP_DEBUG:
	{
		cf.crTextColor = TLP_DEBUG_COLOR;
		break;
	}
	case TLP_DETAIL:
	{
		cf.crTextColor = TLP_DETAIL_COLOR;
		break;
	}
	case TLP_NORMAL:
	{
		cf.crTextColor = TLP_NORMAL_COLOR;
		break;
	}
	case TLP_ERROR:
	{
		cf.crTextColor = TLP_ERROR_COLOR;
		break;
	}
	}
	SetSelectionCharFormat(cf);
}

void CTLogEdit::AddLine(LPCTSTR lpTLogLine, TLOGPRIORITY tlp)
{
	EnterCriticalSection(&m_csTLogEdit);
	PTLOGITEM pItem = new TLOGITEM;
	pItem->line = lpTLogLine;
	pItem->tlp = tlp;
	m_TLogItemQue.AddTail(pItem);
	LeaveCriticalSection(&m_csTLogEdit);
}

void CTLogEdit::AddLine2(LPCTSTR lpTLogLine, TLOGPRIORITY tlp /*= TLP_NORMAL*/)
{
	EnterCriticalSection(&m_csTLogEditStatic);
	PTLOGITEM pItem = new TLOGITEM;
	pItem->line = lpTLogLine;
	pItem->tlp = tlp;
	m_TLogItemQueStatic.AddTail(pItem);
	LeaveCriticalSection(&m_csTLogEditStatic);
}

void CTLogEdit::AddLineStatic(LPCTSTR lpTLogLine, TLOGPRIORITY tlp /*= TLP_NORMAL*/)
{
	EnterCriticalSection(&m_csTLogEditStatic);
	PTLOGITEM pItem = new TLOGITEM;
	pItem->line = lpTLogLine;
	pItem->tlp = tlp;
	m_TLogItemQueStatic.AddTail(pItem);
	LeaveCriticalSection(&m_csTLogEditStatic);
}

void CTLogEdit::LimitLine()
{
	if (GetLineCount() - 1 > m_nLineLimit)
	{
		SetSel(0, LineLength(0) + 1);
		Clear();
	}
}

UINT CTLogEdit::TLogEditThread(LPVOID wParam)
{
	CTLogEdit* pEdit = (CTLogEdit*)wParam;
	PTLOGITEM pItem;
	long pos;
	while (pEdit->m_bRun)
	{
		Sleep(1000);
		while (!pEdit->m_TLogItemQue.IsEmpty())
		{
			EnterCriticalSection(&pEdit->m_csTLogEdit);
			pItem = (PTLOGITEM)pEdit->m_TLogItemQue.RemoveHead();
			LeaveCriticalSection(&pEdit->m_csTLogEdit);
			pos = pEdit->GetTextLength();
			pEdit->SetLogLineColor(pos, pItem->tlp);
			pEdit->ReplaceSel(pItem->line);
			pEdit->LimitLine();
			delete pItem;
			if (pEdit->m_bAutoScroll)
			{
				pEdit->SendMessage(WM_VSCROLL, SB_BOTTOM);
			}
		}
	}
	return 0;
}


int CTLogEdit::TLogEditThreadNew()
{
	PTLOGITEM pItem;
	long pos;
	while (m_bRun) {
		Sleep(1000);
		while (!m_TLogItemQue.IsEmpty())
		{
			EnterCriticalSection(&m_csTLogEdit);
			pItem = (PTLOGITEM)m_TLogItemQue.RemoveHead();
			LeaveCriticalSection(&m_csTLogEdit);
			pos = GetTextLength();
			SetLogLineColor(pos, pItem->tlp);
			ReplaceSel(pItem->line);
			LimitLine();
			delete pItem;
			if (m_bAutoScroll)
			{
				SendMessage(WM_VSCROLL, SB_BOTTOM);
			}
		}
	}
	return 0;
}

int CTLogEdit::TLogTestThread()
{
	for (int i = 0; i < 20; i++)
	{
		AddLine(TEXT("测试DEBUG显示\r\n"), TLP_DEBUG);
		AddLine(TEXT("测试DETAIL显示\r\n"), TLP_DETAIL);
		AddLine(TEXT("测试NORMAL显示\r\n"), TLP_NORMAL);
		AddLine(TEXT("测试ERROR显示\r\n"), TLP_ERROR);
		Sleep(1000);
	}

	return 0;
}

#endif
#endif //_DEBUG


// CTLogEdit 消息处理程序
