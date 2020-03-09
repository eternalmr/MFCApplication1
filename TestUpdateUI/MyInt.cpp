#include "pch.h"
#include "MyInt.h"
#include "resource.h"

MyInt::MyInt() : num_(0)
{

}

MyInt& MyInt::GetInstance()
{
	static MyInt myInt;
	return myInt;
}

void MyInt::addNum()
{
	CProgressCtrl* pProg = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	for (int i = 0; i < 100 ; i++)
	{
		num_++;
		Sleep(1000);
	}
	//CTestUpdateUIDoc *pDoc = getDocument();
}
