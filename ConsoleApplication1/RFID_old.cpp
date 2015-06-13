
#include "stdafx.h"

/*
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
	timer.Start();
	//printf("time.start(): %I64u \n", timer.GetBegin());
	//Sleep(1000);
	timer.Stop();
	printf("time.start(): %I64u \n", timer.GetBegin());
	cout << "timer.stop(): " <<  timer.GetEnd() << endl;

	cout << "timer.time(): " << timer.GetTime() << endl <<endl;

	// 随机数 test 
	random_device rd;	// 生成随机数的速度慢，平均3个时钟周期
	unsigned int rn1;
	
	timer.GetFrequency();
	timer.Start();
	rn1 = rd();
	//cout << "random_device: " << rd() << endl;
	timer.Stop();
	cout << "random_device: " << rn1 << endl;
	cout << "time of random_device: " << timer.GetTime() << endl;
	
	minstd_rand0 mr(timer.GetEnd());	// 生成随机数的速度快，平均1个时钟周期
	cout << endl;
	unsigned int rn2;

	timer.GetFrequency();
	timer.Start();
	rn2 = mr();
	//cout << "minstd_rand0: " << mr() << endl;
	timer.Stop();
	cout << "minstd_rand0: " << rn2 << endl;
	cout << "time of minstd_rand0: " << timer.GetTime() << endl;

	// hash函数测试 
	cout << "hash 函数测试 " << endl;
	hash<string> str_hash;
	hash<int> int_hash;
	//size_t h;
	unsigned int h;

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
	
	// 测试 TagFun 
	Request_Info req;
	//req += itostr(str_hash("QuasiID of tag"));	// QuasiID 
	//req += itostr(h);					// key
	//req += itostr(rn2);					// r1 

	req.QuasiId = str_hash("QuasiID of tag");
	req.key = int_hash(rn2);
	req.r1 = rn1;
	TagFun(req);

	return 0;
}


// 模拟标签行为的函数
Response_Info TagFun(Request_Info rInfo){

	//string QuasiId, Key, r1;
	unsigned int quaId, key, r1;

	cout << endl << "Request_Info: " << rInfo << endl;

	quaId = rInfo.QuasiId;	// 读取 Request_Info内的信息
	key = rInfo.key;
	r1 = rInfo.r1;

	minstd_rand0 minrand(r1&key);		// 生成随机数，使用r1与key的并做为种子
	unsigned int r2 = minrand();

	cout << endl << "TagFun Start ----" << endl;
	cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	cout << "Key: " << key << endl;

	//string str;
	stringstream ss;
	
	ss.clear();
	ss << r1 << r2 << Key;
	ss >> str;
	
	//str += r1;
	//str += r2;
	//str+=key;
	//cout << "str: " << str << "\t str.length: " << str.length() << endl;
	//cout << "输出字串：  " << endl;
	//cout << "1: " << str.substr(0, 10) << "\t2: " << str.substr(10, 10)<< "\t3: " << str.substr(20, 10) << endl;

	//hash<string> str_hash;		// 计算Hash值
	//string h;
	//h = itostr(str_hash(str));

	hash<unsigned int > int_hash;		// 计算Hash值
	unsigned int h = int_hash(r1&r2&key);

	cout << "hash(r1,r2,key): " << h << endl;

	
	Response_Info ri;			// 生成响应信息
	ri.QuasiId =quaId;
	ri.r2 = r2;
	ri.h = h;
	//ri += QuasiId;
	//ri += r2;
	//ri += h;
	cout << endl << "Response_Info: " << ri << endl;

	return  ri;
}

std::ostream& operator<<(ostream & out, Request_Info value){
	out << value.QuasiId << " " << value.key << " " << value.r1;
	return out;
}

std::ostream& operator<<(ostream & out, Response_Info value){
	out << value.QuasiId << " " << value.r2 << " " << value.h;
	return out;
}

inline string itostr(size_t i){		// 将整形数转换为字符串
	//std::stringstream ss;
	//ss << i;
	//return ss.str();

	char buf[20];
	sprintf_s(buf, "%010.10u", i);
	return buf;
}

inline unsigned int strtoi(string s){		// 将字符串转换为整形数
	int i = atoi(s.c_str());
	return i;
}

Result_Info ReaderFun(Response_Info, string r1){ // 模拟阅读器行为的函数
	
	
	return '0';
}

*/
