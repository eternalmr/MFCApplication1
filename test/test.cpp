// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <fstream>
#include <windows.h>

using namespace std;

class A {
public:
	A(int i) : i_(i) { cout << "构造函数调用" << endl; }
	A(const A &Aobj) : i_(Aobj.i_) { cout << "拷贝构造函数调用" << endl; }
	~A() { cout << "析构函数调用" << endl; }

	int i_;
};

void myfun()
{
	A a(2);
	fstream outfile;
	outfile.open("C:\\Users\\eternalmr\\Desktop\\test.txt", ios::out);

	for (int i = 0; i < 20 ; i++)
	{
		cout << "A.i = " << a.i_ << " : "<< i << endl;
		outfile << "A.i = " << a.i_ << " : " << i << endl;
		Sleep(5);
	}


}

int main()
{
	//A a(1); 
	thread t1(myfun);
	t1.detach();

	//thread t2(myfun, A(2));
	//t2.detach();

	for (int i = 0;i<10;i++)
	{
		Sleep(5);
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
