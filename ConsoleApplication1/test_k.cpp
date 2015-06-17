// 测试k匿名隐私模型

#include "stdafx.h"
#include "test_k.h" 
using namespace std;

// 默认情况下 k = 5
TestK::TestK(){
	k = 5;
}

TestK::TestK(int tmp){
	k = tmp;
}

// 向数据库中插入数据
int TestK::DataInsert(){

	hash<unint> int_hash;

	// 开始操作数据库
	ADOConn dbConn;
	try{
		dbConn.OnInitADOConn();
		if (dbConn.m_pConnection != NULL && dbConn.m_pConnection->State == adStateOpen)
			cout << endl << "DB connection success." << endl;
		else{
			cout << endl << "DB connection failure." << endl;
			return 2;
		}
		// 向数据库中添加数据
		ostringstream sql;
		unint count = 0;
		cout << endl << "Start Insert Data...." << endl;
		for (int i = 5; i > 0; --i){
			sql.seekp(0);
			sql.clear();
			sql.str("");
			sql << "insert into Tags values ( "
				<< int_hash(_Random_device())
				<< ", "
				<< int_hash(_Random_device())
				<< " )";
			
			if (dbConn.ExecuteSQL(sql.str().c_str()))
				++count;
		}
		dbConn.ExitConnect();
		std::cout << endl << "The number of record is " << count << " ." << endl;
	}
	catch (_com_error e){
		dbConn.ExitConnect();
	}

}


std::ostream& operator<<(ostream & out, TestK::Request_Info value){		// 输出 查询信息
	out << value.QuasiId << " " << value.key << " " << value.r1;
	return out;
}

std::ostream& operator<<(ostream & out, TestK::Response_Info value){		// 输出 响应信息
	out << value.QuasiId << " " << value.r2 << " " << value.h;
	return out;
}

// 模拟标签行为的函数
TestK::Response_Info TestK::TagFun(TestK::Request_Info req){

	std::cout << std::endl << "Request_Info: " << req << endl;

	unint quaId, key, r1;
	quaId = req.QuasiId;	// 读取 Request_Info内的信息
	key = req.key;
	r1 = req.r1;

	minstd_rand0 minrand(r1&key);		// 生成随机数，使用r1与key的并做为种子
	unsigned int r2 = minrand();

	std::cout << endl << "TagFun Start ----" << endl;
	std::cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	std::cout << "Key: " << key << endl;

	hash<unsigned int > int_hash;		// 计算Hash值
	unsigned int h = int_hash(r1&r2&key);
	std::cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// 生成响应信息
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	std::cout << endl << "Response_Info: " << res << endl;

	return  res;
}

// 模拟阅读器行为的函数
TestK::Result_Info TestK::ReaderFun(Response_Info res, unint r1){ 
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

// 模拟交互过程的函数
unsigned _int64 TestK::ProtocolFun(){
	MyTimer timer;

	timer.Start();

	random_device rd;	// 生成随机数
	unint r1 = rd();

	hash<string> str_hash;
	unint qua = str_hash("QuasiID of Tag");

	hash<unint> int_hash;
	unint key = int_hash(qua&r1);

	Request_Info ri;		// 生成查询信息
	ri.QuasiId = qua;
	ri.key = key;
	ri.r1 = r1;

	// 调用模拟标签的函数
	std::cout << endl << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// 调用阅读器的函数
	std::cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, r1);

	timer.Stop();			// 计时器终止
	cout << "Time of process: " << timer.GetTime() << endl;

	cout << endl << "Result: " << endl;
	if (result == '1')
		cout << "Success" << endl;
	else cout << "Failure" << endl;

	return 1;
}