// RFID.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

	MyTimer timer;

	timer.Start();

	random_device rd;	// ���������
	unint r1 = rd();

	hash<string> str_hash;
	unint qua = str_hash("QuasiID of Tag");

	hash<unint> int_hash;
	unint key = int_hash(qua&r1);

	Request_Info ri;		// ���ɲ�ѯ��Ϣ
	ri.QuasiId = qua;
	ri.key = key;
	ri.r1 = r1;

	// ����ģ���ǩ�ĺ���
	cout << endl << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// �����Ķ����ĺ���
	cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, r1);

	timer.Stop();			// ��ʱ����ֹ

	cout << endl << "Result: " << endl;
	if (result == '1')
		cout << "Success" << endl;
	else cout << "Failure" << endl;

	return 0;
}

string itostr(size_t i){		// ��������ת��Ϊ�ַ���
	char buf[20];
	sprintf_s(buf, "%010.10u", i);
	return buf;
}

unint strtoi(string s){		// ���ַ���ת��Ϊ������
	int i = atoi(s.c_str());
	return i;
}
