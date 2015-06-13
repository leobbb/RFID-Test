// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ��ʱ�� ��ʹ�� 
	cout << "My Timer Class	----" << endl;
	MyTimer timer;
	cout << "timer.GetFrequency():  "<< timer.GetFrequency() << endl;
	timer.Start();
	//printf("time.start(): %I64u \n", timer.GetBegin());
	//Sleep(1000);
	timer.Stop();
	printf("time.start(): %I64u \n", timer.GetBegin());
	cout << "timer.stop(): " <<  timer.GetEnd() << endl;

	cout << "timer.time(): " << timer.GetTime() << endl <<endl;

	// ����� test 
	random_device rd;	// ������������ٶ�����ƽ��3��ʱ������
	unsigned int rn1;
	
	timer.GetFrequency();
	timer.Start();
	rn1 = rd();
	//cout << "random_device: " << rd() << endl;
	timer.Stop();
	cout << "random_device: " << rn1 << endl;
	cout << "time of random_device: " << timer.GetTime() << endl;
	
	minstd_rand0 mr(timer.GetEnd());	// ������������ٶȿ죬ƽ��1��ʱ������
	cout << endl;
	unsigned int rn2;

	timer.GetFrequency();
	timer.Start();
	rn2 = mr();
	//cout << "minstd_rand0: " << mr() << endl;
	timer.Stop();
	cout << "minstd_rand0: " << rn2 << endl;
	cout << "time of minstd_rand0: " << timer.GetTime() << endl;

	// hash�������� 
	cout << "hash �������� " << endl;
	hash<string> str_hash;
	size_t h;
	
	timer.Start();
	h = str_hash("test");
	timer.Stop();

	cout << "hash('test'): " << h << endl;
	cout << "time of hash: " << timer.GetTime() << endl << endl;

	timer.GetFrequency();
	timer.Start();
	Sleep(1);
	timer.Stop();
	cout << "time of Sleep(1000): " << timer.GetTime() << endl;
	
	return 0;
}

// ģ���ǩ��Ϊ�ĺ���
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