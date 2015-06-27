// 测试 Hash-Lock 隐私模型

#include "stdafx.h"
#include "test_hl.h"

using namespace std;

// 初始化数据库中的数据
bool TestHL::InitData(){
	// 如果数据正确，则返回TRUE。
	if (TestData())
		return TRUE;

	// 初始化数据
	cout << endl << "Delete All Data..." << endl;
	string sql = "";
	sql = "TRUNCATE TABLE [Tags_HL]";
	if (adoConn.ExecuteSQL(sql.c_str()))
		cout << "\tOperating is done." << endl;
	else
		return FALSE;

	cout << endl << "Insert New Data..." << endl;
	if (InsertData() == 1000)
		cout << "\tOperating is done." << endl;
	else
		return FALSE;

	return TRUE;
}

bool TestHL::TestData(){
	string sql = "";

	//测试数据库中记录总数 
	sql = "select count(*) as num from Tags_HL";
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
		return FALSE;
	
	int count = adoConn.m_pRecordset->GetCollect("num").intVal;
	adoConn.CloseRecordset();
	if (count < 1000)
		return FALSE;

	return TRUE;
}

// 向数据库中插入数据
int TestHL::InsertData(){

	hash<unint> int_hash;

	// 开始操作数据库
	//ADOConn dbConn;
	try{

		// 向数据库中添加数据
		ostringstream sql;
		unint count = 0;
		cout << endl << "Start Insert Data...." << endl;

		for (int i = 1000; i > 0; --i){		
			sql.seekp(0);
			sql.clear();
			sql.str("");
			sql << "insert into Tags_HL values ( "
				<< int_hash(_Random_device())
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


// 模拟标签行为的函数
TestHL::Response_Info TestHL::TagFun(TestHL::Request_Info req){
	// 获取标签的信息
	unint id, key;
	id = req.id;
	key = req.key;

	// 生成随机数
	random_device rd;
	unint r = rd();

	// 计算hash值
	hash<unint> int_hash; 
	unint h = int_hash(id&r);

	// 生成响应信息
	Response_Info res;
	res.r = r;
	res.h = h;
	
	return res;
}

// 模拟阅读器行为的函数
TestHL::Result_Info TestHL::ReaderFun(TestHL::Response_Info res){
	unint r, h;
	r = res.r;
	h = res.h;

	// 数据库中存储的标签Id
	unint id, h1; 
	hash<unint> int_hash;

	// 构造查询字符串，获取所以的标签信息
	string sql;
	sql = "select [Id],[Key] from Tags_HL";
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pConnection->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
		return FALSE;
	
	// 遍历结果集
	while (adoConn.m_pRecordset->adoEOF == 0){
		id = adoConn.m_pRecordset->GetCollect("Id").uintVal;
		h1 = int_hash(id&r);
		if (h1 == h)
		{
			adoConn.CloseRecordset();
			return TRUE;
		}
		adoConn.m_pRecordset->MoveNext();
	}

	adoConn.CloseRecordset();
	return FALSE;
}

// 模拟交互过程的函数
unsigned _int64 TestHL::ProtocolFun(const int& tag){
	// 获取被选标签的信息
	string sql;
	sql = "select [Id], [Key] from Tags_HL where Num=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	{
		cout << endl << "Tag[" << tag << "] isn't in DataBase." << endl;
		return 0;
	}

	// 生成查询信息
	Request_Info req;
	req.id= adoConn.m_pRecordset->GetCollect("Id").uintVal;
	req.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();

	// 计时器
	MyTimer timer;
	// 初始化随机数生成器
	minstd_rand0 minrand(timer.GetBegin());

	timer.Start();

	// 调用模拟标签的函数
	Response_Info res = TagFun(req);

	// 调用阅读器的函数
	Result_Info result = ReaderFun(res);

	// 计时器终止
	timer.Stop();

	return  timer.GetTime();

}