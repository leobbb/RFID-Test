// k匿名隐私模型

#include "stdafx.h"
using namespace std;


// 模拟标签行为的函数
Response_Info TagFun(Request_Info req){

	cout << endl << "Request_Info: " << req << endl;

	unint quaId, key, r1;
	quaId = req.QuasiId;	// 读取 Request_Info内的信息
	key = req.key;
	r1 = req.r1;

	minstd_rand0 minrand(r1&key);		// 生成随机数，使用r1与key的并做为种子
	unsigned int r2 = minrand();

	cout << endl << "TagFun Start ----" << endl;
	cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	cout << "Key: " << key << endl;

	hash<unsigned int > int_hash;		// 计算Hash值
	unsigned int h = int_hash(r1&r2&key);
		cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// 生成响应信息
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	cout << endl << "Response_Info: " << res << endl;

	return  res;
}

std::ostream& operator<<(ostream & out, Request_Info value){		// 输出 查询信息
	out << value.QuasiId << " " << value.key << " " << value.r1;
	return out;
}

std::ostream& operator<<(ostream & out, Response_Info value){		// 输出 响应信息
	out << value.QuasiId << " " << value.r2 << " " << value.h;
	return out;
}

// 模拟阅读器行为的函数
Result_Info ReaderFun(Response_Info res, unint r1){ 
	// 读取响应信息
	unint qua, r2, h;
	qua = res.QuasiId;
	r2 = res.r2;
	h = res.h;

	// 访问数据库
	unint key2 = 12345;		// 数据库中存储的标签的key
	hash<unint> int_hash;
	unint h1 = int_hash(r1&r2&key2);

	if (h1 == h)
		return '1';

	return '0';
}