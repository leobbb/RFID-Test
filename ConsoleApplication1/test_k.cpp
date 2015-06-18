// 测试k匿名隐私模型

#include "stdafx.h"

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
	//ADOConn dbConn;
	try{

		// 向数据库中添加数据
		ostringstream sql;
		unint count = 0;
		size_t quaId;
		cout << endl << "Start Insert Data...." << endl;
		cout << "k = " << k << endl;
		for (int i = 1000 / k; i > 0; --i){		// 以k进行分组
			quaId = int_hash(_Random_device());	// 同一组使用相同的准标识符
			for (int j = k; j > 0; --j){
				sql.seekp(0);
				sql.clear();
				sql.str("");
				sql << "insert into Tags values ( "
					<< quaId
					<< ", "
					<< int_hash(_Random_device())
					<< " )";
				if (adoConn.ExecuteSQL(sql.str().c_str()))
					++count;
			}
		}
		for (int i = 1000 % k; i > 0; --i)
		{
			sql.seekp(0);
			sql.clear();
			sql.str("");
			sql << "insert into Tags values ( "
				<< quaId
				<< ", "
				<< int_hash(_Random_device())
				<< " )";

			if (adoConn.ExecuteSQL(sql.str().c_str()))
				++count;
		}
		std::cout << endl << "The number of record is " << count << " ." << endl;
		return count;
	}
	catch (_com_error e){
		return -1;
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
	//std::cout << std::endl << "Request_Info: " << req << endl;
	//std::cout << endl << "Start TagFun ..." << endl;	
	// 读取 Request_Info内的信息
	unint quaId, key, r1;
	quaId = req.QuasiId;	
	key = req.key;
	r1 = req.r1;
	hash<unint> int_hash;		// 计算Hash值

	// 生成随机数，使用r1与key的并做为种子
	minstd_rand0 minrand(r1&key);		
	unint r2 = minrand();

	//std::cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	//std::cout << "Key: " << key << endl;
	
	unint h = int_hash(r1&r2&key);	// 计算Hash值
	//std::cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// 生成响应信息
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	//std::cout << endl << "Response_Info: " << res << endl;
	//std::cout << endl << "TagFun end." << endl;
	return  res;
}

// 模拟阅读器行为的函数
TestK::Result_Info TestK::ReaderFun(Response_Info res, unint r1){ 
	// 读取响应信息
	unint qua, r2, h;
	qua = res.QuasiId;
	r2 = res.r2;
	h = res.h;
	unint key, h1;		// 数据库中存储的标签密钥, 新的Hash值
	hash<unint> int_hash;		// 计算Hash值

	//cout << endl << "Start ReaderFun ... QuasiId = " << qua << endl;
	// 访问数据库
	//ADOConn adoConn;
	string sql;
	sql = "select [QuasiId],[Key] from Tags where QuasiId = ";
	sql += itostr(qua);
	_RecordsetPtr pRecordset = adoConn.GetRecordSet(sql.c_str());
	
	if (pRecordset->GetRecordCount() == 0)
		return false;
	// 遍历记录集
	while (pRecordset->adoEOF == 0){
		key = pRecordset->GetCollect("Key").uintVal;
		h1 = int_hash(r1&r2&key);
		if (h1 == h)
		{
			//cout << endl << "Test end." << endl;
			return TRUE;
		}
		pRecordset->MoveNext();
	}

	//cout << endl << "ReaderFun end." << endl;
	return FALSE;
}

// 模拟交互过程的函数
unsigned _int64 TestK::ProtocolFun(const int & tag){
	string sql;
	sql = "select [QuasiId], [Key] from Tags where Id=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	{
		cout << endl << "Tag[" << tag << "] isn't in DataBase." << endl;
		return 0;
	}

	//cout << endl << "Start testing k-anonymous model...." << endl;
	//cout << "\tTag[" << tag << "]" << endl;
	// 生成查询信息
	Request_Info ri;
	ri.QuasiId = adoConn.m_pRecordset->GetCollect("QuasiId").uintVal;
	ri.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;

	// 计时器
	MyTimer timer;
	// 初始化随机数生成器
	minstd_rand0 minrand(timer.GetBegin());

	timer.Start();

	// 生成随机数
	//random_device rd;	
	unint R1 = minrand();

	//hash<string> str_hash;
	//unint qua = str_hash("QuasiID of Tag");
	//hash<unint> int_hash;
	//unint key = int_hash(qua&r1);

	ri.r1 = R1;

	// 调用模拟标签的函数
	//std::cout << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// 调用阅读器的函数
	//std::cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, R1);

	timer.Stop();			// 计时器终止

	//cout << endl << "Result: " << endl;
	//if (result == TRUE)
	//	cout << "\tSuccess! Tag is authentication." << endl;
	//else cout << "\tFailure" << endl;
	//cout << endl << "Test end." << endl;

	return  timer.GetTime();
}

// 模拟交互过程的函数 无函数调用
unsigned _int64 TestK::Protocol(const int & tag){

}