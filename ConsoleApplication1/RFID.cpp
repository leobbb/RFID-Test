// RFID.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

	minstd_rand0 mr(time(NULL));	// ���������
	unint r1 = mr();

	hash<string> str_hash;
	unint qua = str_hash("QuasiID of Tag");

	hash<unint> int_hash;
	unint key = int_hash(qua&r1);

	Request_Info ri;		// ���ɲ�ѯ��Ϣ
	ri.QuasiId = qua;
	ri.key = key;
	ri.r1 = r1;

	// ����ģ���ǩ�ĺ���
	Response_Info res = TagFun(ri);

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
