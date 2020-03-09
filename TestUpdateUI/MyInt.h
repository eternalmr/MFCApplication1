#pragma once
#include <thread>

class MyInt
{
private:
	MyInt();

public:
	static MyInt& GetInstance();
	void addNum();

public:
	int num_;
	std::thread MyThread;
};

