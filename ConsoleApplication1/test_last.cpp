// 测试 LAST	 协议

#include "stdafx.h"
#include "test_last.h"

using namespace std;

// 向数据库中插入数据
int TestLAST::InsertData(){

	hash<unint> int_hash;

	// 开始操作数据库
	//ADOConn dbConn;
	try{
		// 向数据库中添加数据
		string sql = "";
		unint count = 0;
		cout << endl << "\tStart Insert Data...." << endl;

		for (int i = 1000; i > 0; --i){
			sql = "insert into Tags_LAST values ( ";
			sql += itostr(int_hash(_Random_device()));
			sql += ", ";
			sql += itostr(int_hash(_Random_device()));
			sql += " )";		
			if (adoConn.ExecuteSQL(sql.c_str()))
				++count;
		}
		std::cout << endl << "\tThe number of record is " << count << " ." << endl;
		return count;
	}
	catch (_com_error e){
		return -1;
	}
}

// 测试数据是否正确
bool TestLAST::TestData(){
	string sql = "";

	//测试数据库中记录总数 
	sql = "select count(*) as num from Tags_LAST";
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
		return FALSE;

	unint count = adoConn.m_pRecordset->GetCollect("num").uintVal;
	adoConn.CloseRecordset();
	if (count < 1000)
		return FALSE;

	return TRUE;
}

// 初始化数据库中的数据
bool TestLAST::InitData(){
	// 如果数据正确，则返回TRUE。
	if (TestData())
		return TRUE;

	// 初始化数据
	cout << endl << "Delete All Data..." << endl;
	string sql = "";
	sql = "TRUNCATE TABLE [Tags_LAST]";
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


// 模拟标签行为的函数
TestLAST::Response_Info TestLAST::TagFun(TestLAST::Request_Info req){

	// 读取 Request_Info内的信息
	unint index, key, r1;
	index = req.index;
	key = req.key;
	r1 = req.r1;
	hash<unint> int_hash;		

	// 生成随机数 r2
	unint r2 = _Random_device();
	
	// 计算Hash值
	unint h = int_hash(r1&r2&key);	

	// 生成响应信息
	Response_Info res;			
	res.index = index;
	res.r2 = r2;
	res.v = h;

	return  res;
}

// 模拟阅读器行为的函数
TestLAST::Result_Info TestLAST::ReaderFun(Response_Info res, unint r1,Refresh_Info & refresh){
	// 读取响应信息
	unint index, r2, v;
	index = res.index;
	r2 = res.r2;
	v = res.v;
	
	// 数据库中存储的标签密钥, 新的Hash值
	unint key, v1;		
	hash<unint> int_hash;		// 计算Hash值

	string sql;
	sql = "select [Index],[Key] from [Tags_LAST] where [Index] = ";
	sql += itostr(index);
	_RecordsetPtr pRecordset = adoConn.GetRecordSet(sql.c_str());

	if (pRecordset->GetState() == adStateClosed || pRecordset->GetRecordCount() == 0)
		return FALSE;

	// 遍历记录集 （最多包含1条记录）
	key = pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();
	v1 = int_hash(r1&r2&key);

	if (v1 == v)
	{
		//cout << endl << "Test end." << endl;
		
		unint index1 = int_hash(r1&r2&index&key);	// 计算得到标签新的索引值
		unint key1 = int_hash(r1&r2&key);			// 计算得到标签新的密钥
		refresh = int_hash(r1&r2&key1);					// 得到刷新标签的验证信息

		sql = "UPDATE [Tags_LAST] SET [Index] =	";
		sql += itostr(index1);
		sql += ", [Key] = ";
		sql += itostr(key1);
		sql += "  WHERE [Index]= ";
		sql += itostr(index);
		if (adoConn.ExecuteSQL(sql.c_str()))
		{
			// 刷新成功
			return TRUE;
		}
	}
	return FALSE;
}

// 模拟标签刷新的过程
bool TestLAST::TagFun(Request_Info req, Response_Info res, Refresh_Info refresh){
	unint index = req.index;
	unint key = req.key;
	unint r1, r2;
	r1 = req.r1;
	r2 = res.r2;
	hash<unint> int_hash;		// 计算Hash值

	unint index1 = int_hash(r1&r2&index&key);
	unint key1 = int_hash(r1&r2&key);
	unint refresh1 = int_hash(r1&r2&key1);

	if (refresh1 == refresh){
		// 通过合法阅读器认证，然后刷新标签信息
		index = index1;
		key = key1;
		return TRUE;
	}
	else{
		// 非法认证，不刷新标签信息
		return FALSE;
	}
}


// 模拟交互过程的函数
unsigned _int64 TestLAST::ProtocolFun(const int & tag){
	// 获取被选标签的信息
	string sql;
	sql = "select [Index], [Key] from Tags_LAST where Num=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	{
		cout << endl << "Tag-" << tag << " isn't in DataBase." << endl;
		return 0;
	}

	// 生成查询信息
	Request_Info ri;
	ri.index = adoConn.m_pRecordset->GetCollect("Index").uintVal;
	ri.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();

	// 计时器
	MyTimer timer;

	timer.Start();

	// 生成随机数
	unint R1 = _Random_device();
	ri.r1 = R1;

	// 调用模拟标签的函数
	Response_Info res = TagFun(ri);

	// 标签用于刷新的验证信息
	Refresh_Info refresh = 0;

	// 调用模拟阅读器的函数
	Result_Info result = ReaderFun(res, R1, refresh);

	// 认证通过， 刷新标签
	if (result){
		TagFun(ri, res, refresh);
	}

	// 计时器终止
	timer.Stop();

	return  timer.GetTime();
}
