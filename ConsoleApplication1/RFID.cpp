// RFID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

ADOConn adoConn;				// 定义 全局数据库连接对象

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Starting... " << endl;
	try{
		// 测试数据库连接
		adoConn.OnInitADOConn();
		if (adoConn.m_pConnection != NULL && adoConn.m_pConnection->State == adStateOpen)
			cout << endl << "DB connection success." << endl;
		else{
			cout << endl << "DB connection failure." << endl;
			return -1;
		}
		string sql = "select count(*) as num from Tags ";
		adoConn.GetRecordSet(sql.c_str());
		cout << endl << "Data count(*) : " << adoConn.m_pRecordset->GetCollect("num").uintVal << endl;

		// 随机选取10个标签作为实验对象
		int tags[10];
		int i = 0;
		for (i = 0; i < 10; ++i){
			tags[i] = _Random_device() % 1000 + 1;  // 取1...1000之间的数
		}

	//	// 将实验对象逐个传入 ProtocolFun 函数进行实验
	//	// 测试 k-匿名模型
	//	TestK test_k(3);
	//	// 可能需要先测试数据是否正确、完整
	//	if (test_k.InitData())
	//		cout << endl << "Test Starting..." << endl;
	//	else{
	//		cout << endl << "Data initial failure." << endl;
	//		return -1;
	//	}
	//	
	//	cout << endl << "Result of k-anonymous: \n\tk = " << test_k.GetK() << endl;
	//	while (i){
	//		int tag = tags[--i]; 
	//		LONGLONG lltime = 0;
	//		for (int j = 0; j < 10; ++j){
	//			lltime += test_k.ProtocolFun(tag);
	//		}
	//		cout << "Tag[" << tag << "]:\t"
	//			<< "Time is " << lltime / 10 << " ns." << endl;
	//	}
	//	cout << endl << "End." << endl;
	}
	catch (_com_error){

	}

	return 0;
}

// 将整形数转换为字符串
string itostr(size_t i){		
	char buf[20];
	sprintf_s(buf, "%u", i);
	return buf;
}

// 将字符串转换为整形数
unint strtoi(string s){		
	int i = atoi(s.c_str());
	return i;
}

// 输出异常信息
void printerror(_com_error e){	// 输出异常信息
	//显示错误信息
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	printf("Error\n");
	printf("\tCode = %08lx\n", e.Error());
	printf("\tCode meaning = %s\n", e.ErrorMessage());
	printf("\tSource = %s\n", (LPCSTR)bstrSource);
	printf("\tDescription = %s\n", (LPCSTR)bstrDescription);

}
