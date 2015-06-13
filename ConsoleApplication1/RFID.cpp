// RFID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

	minstd_rand0 mr(time(NULL));	// 生成随机数
	unint r1 = mr();

	hash<string> str_hash;
	unint qua = str_hash("QuasiID of Tag");

	hash<unint> int_hash;
	unint key = int_hash(qua&r1);

	Request_Info ri;		// 生成查询信息
	ri.QuasiId = qua;
	ri.key = key;
	ri.r1 = r1;

	// 调用模拟标签的函数
	Response_Info res = TagFun(ri);

	return 0;
}

string itostr(size_t i){		// 将整形数转换为字符串
	char buf[20];
	sprintf_s(buf, "%010.10u", i);
	return buf;
}

unint strtoi(string s){		// 将字符串转换为整形数
	int i = atoi(s.c_str());
	return i;
}
