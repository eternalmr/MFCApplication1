#pragma once

enum  TLOGPRIORITY
{
	TLP_DEBUG = 0,
	TLP_DETAIL,
	TLP_NORMAL,
	TLP_ERROR
};

class CTLog
{
public:
	CTLog();

	static UINT TLogThread(LPVOID wParam);
	int TLogThreadNew();
	void OpenNewFile();
	BOOL AddLine(LPCTSTR lpTLogLine, TLOGPRIORITY tlp = TLP_NORMAL);

	BOOL m_bRun;

private:
	CRITICAL_SECTION m_csTLog;
	CStdioFile* m_pFile;
	CString m_strTLogBuffer;
	CString m_strTLogFilePath;
	TLOGPRIORITY m_TLogPriority;
	unsigned long long m_ullMaxFileSize;
};

