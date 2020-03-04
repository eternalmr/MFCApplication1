#include "pch.h"
#include "CTLog.h"

CTLog::CTLog() : m_bRun(FALSE),
				//m_pFile(nullptr),
				m_TLogPriority(TLP_DEBUG),
				m_ullMaxFileSize(1024*1024),
				m_strTLogFilePath(_T("C:\\Users\\eternalmr\\Desktop"))
{
	InitializeCriticalSection(&m_csTLog);
	m_pFile = new CStdioFile(m_strTLogFilePath + _T("//debug.log"), CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone);
	//m_pFile = new CStdioFile(m_strTLogFilePath + _T("//debug.log"), 
	//	CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone, NULL);
	//CRITICAL_SECTION m_csTLog;
	//CString m_strTLogBuffer; 默认初始化为空
	//CString m_strTLogFilePath; 默认初始化为空
}

UINT CTLog::TLogThread(LPVOID wParam)
{
	CTLog* pLog = (CTLog*)wParam;
	while (pLog->m_bRun)
	{
		Sleep(3000);
		EnterCriticalSection(&pLog->m_csTLog);
		if (pLog->m_strTLogBuffer.GetLength())
		{
			pLog->m_pFile->WriteString(pLog->m_strTLogBuffer);
			pLog->m_pFile->Flush();
			pLog->m_strTLogBuffer.Empty();
		}
		LeaveCriticalSection(&pLog->m_csTLog);
		if (pLog->m_pFile->m_hFile != INVALID_HANDLE_VALUE)
		{
			if (pLog->m_pFile->GetLength() >= pLog->m_ullMaxFileSize)
			{
				pLog->OpenNewFile();
			}
		}
	}
	EnterCriticalSection(&pLog->m_csTLog);
	if (pLog->m_pFile->m_hFile != INVALID_HANDLE_VALUE)
	{
		pLog->m_pFile->WriteString(pLog->m_strTLogBuffer + _T("/r/n"));
		pLog->m_pFile->Flush();
	}
	LeaveCriticalSection(&pLog->m_csTLog);
	return 0;
}

int CTLog::TLogThreadNew()
{
	while (m_bRun)
	{
		Sleep(3000);
		EnterCriticalSection(&m_csTLog);
		if (m_strTLogBuffer.GetLength())
		{
			m_pFile->WriteString(m_strTLogBuffer);
			m_pFile->Flush();
			m_strTLogBuffer.Empty();
		}
		LeaveCriticalSection(&m_csTLog);
		if (m_pFile->m_hFile != INVALID_HANDLE_VALUE)
		{
			if (m_pFile->GetLength() >= m_ullMaxFileSize)
			{
				OpenNewFile();
			}
		}
	}
	EnterCriticalSection(&m_csTLog);
	if (m_pFile->m_hFile != INVALID_HANDLE_VALUE)
	{
		m_pFile->WriteString(m_strTLogBuffer + _T("/r/n"));
		m_pFile->Flush();
	}
	LeaveCriticalSection(&m_csTLog);
	return 0;
}

void CTLog::OpenNewFile()
{
	EnterCriticalSection(&m_csTLog);
	m_pFile->Close();
	CFileStatus fs;
	CFile::GetStatus(m_strTLogFilePath + _T("//debug.log"), fs);
	CFile::Rename(m_strTLogFilePath + _T("//debug.log"), m_strTLogFilePath + _T("//debug_") + fs.m_ctime.Format(_T("%Y%m%d_%H%M%S")) + _T(".log"));
	m_pFile->Open(m_strTLogFilePath + _T("//debug.log"), CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyNone, NULL);
	m_pFile->Write("/377/376", 2);
	LeaveCriticalSection(&m_csTLog);
}

BOOL CTLog::AddLine(LPCTSTR lpTLogLine, TLOGPRIORITY tlp)
{
	if (tlp < m_TLogPriority)
	{
		return FALSE;
	}
	if (_tcslen(lpTLogLine))
	{
		EnterCriticalSection(&m_csTLog);
		m_strTLogBuffer += lpTLogLine;
		LeaveCriticalSection(&m_csTLog);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
