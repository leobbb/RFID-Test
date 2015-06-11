// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Hello!" << std::endl;
	//Request_Info rInfo;
	//rInfo.key = "1002901";
	//rInfo.r1 = 10;

	//cout << rInfo.key << " + " << rInfo.QuasiId << endl;
	//srand((unsigned int)time(NULL));
	//cout << rand() << "  +  " << time(NULL) << " + " << RAND_MAX << endl;
	//cout << sizeof(int) << " + " << UINT_MAX;

	//cout << endl;
	//for (int i = 10; i > 0; --i){
	//	cout << rand() << " ";
	//}
	//cout << endl << "sizeof(double)" << sizeof(double);
	//union {
	//	int a;
	//	char b;
	//}c;

	//c.a = 1;
	//cout << "c.a: " << c.a << endl;
	//cout << "c.b: " << (int)c.b << endl;
	//cout << "CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << endl;

	//char ch = '1';
	//cout << "char ch = " << (int)ch << endl;

	// 计时器 的使用 
	cout << "My Timer Class	----" << endl;
	MyTimer timer;
	cout << "timer.GetFrequency():  "<< timer.GetFrequency() << endl;
	unsigned _int64 begin= timer.Start();
	printf("time.start(): %I64u \n", begin);
	Sleep(1000);
	unsigned _int64 end = timer.Stop();
	cout << "timer.stop(): " <<  end << endl;

	cout << "timer.time(): " << timer.GetTime() << endl;


	return 0;
}

// 模拟标签行为的函数
Response_Info TagFun(Request_Info rInfo){

	string QuasiId, Key;
	int r1;

	QuasiId = rInfo.QuasiId;
	Key = rInfo.key;
	r1 = rInfo.r1;

	int r2 = rand();

	Response_Info ri;

	return  ri;
}