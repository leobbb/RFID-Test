// RFID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

ADOConn adoConn;				// 定义 全局数据库连接对象

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\tHello! Task will start. " << endl;
	try{
		// 测试数据库连接
		adoConn.OnInitADOConn();
		if (adoConn.m_pConnection != NULL && adoConn.m_pConnection->State == adStateOpen)
			cout << endl << "Database connection success." << endl;
		else{
			cout << endl << "Database connection failure." << endl;
			return -1;
		}

		// 随机选取10个标签作为实验对象
		cout << endl <<"Select 10 tags for experiment:" << endl;
		int tags[10];
		int i = 0;
		for (i = 0; i < 10; ++i){
			tags[i] = _Random_device() % 1000 + 1;  // 取1...1000之间的数
			cout << "Tag" << i + 1 << ": " << tags[i] << "\t";
		}

		//cout << endl << "argc: " << argc << endl;
		//i = 0;
		//while (argc--){			
		//	wcout << "argv[" << i << "] = " << argv[i] << endl;
		//	++i;
		//}

		//wcout << "test L string : " << L"long string with L" << endl;
		//_TCHAR *tchar;
		//tchar = _T("right");

		//if (!_tcscmp(tchar, argv[1]))
		//	cout << "argv[1] is same to \"right\"." << endl;
		//else
		//	cout << "No right" << endl;
		//

		cout << endl;
		cout << "Test for k-Anonymout Model, input k" << endl;
		cout << "Test for Hash-Lock Protocol, input h" << endl;
		cout << "Test for LAST Protocol, input l" << endl;
		cout << "Run All Test, input a" << endl;
		cout << "Exit Program, input e" << endl;

Run_Again:
		cout << endl << "Select a character:\t";
		char ch;
		cin >> ch;
		switch (ch)
		{
		case 'k':
			Run_K(tags,10);
			break;
		case 'h':
			Run_HL(tags,10);
			break;
		case 'l':
			Run_L(tags, 10);
			break;
		case 'a':
			Run_K(tags, 10);
			Run_HL(tags, 10);
			Run_L(tags, 10);
			break;
		case 'e':
			cout << endl << "Exit Program." << endl;
			return 0;
		default:
			cout << "Input Wrong." << endl;
			break;
		}
		goto Run_Again;
	}
	catch (_com_error){
		cout << "Something error." << endl;
		return -1;
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

// 执行k-匿名模型的测试
int Run_K(const int tags[], size_t size){

	// 测试 k-匿名模型
	cout << endl << "\tTest for k-Anonymous Model" << endl;
	TestK test_k(3);
	// 可能需要先测试数据是否正确、完整
	if (test_k.InitData()){
		cout << endl << "Data initial succeed." << endl;
		cout << endl << "Test Starting..." << endl;
	}
	else{
		cout << endl << "Data initial failure." << endl;
		return -1;
	}
		
	cout << endl << "Result: \tk = " << test_k.GetK() << endl;
	size_t i = 0, j = 0;
	LONGLONG lltime = 0;
	// 将实验对象逐个传入 ProtocolFun 函数进行实验
	while (i < size){
		int tag = tags[i++];
		for (j = 0, lltime = 0; j < 10; ++j){
			lltime += test_k.ProtocolFun(tag);
		}
		cout << "Tag" << i << " (" << tag << "):\t"
			<< "Time is " << lltime / 10 << " ns." << endl;
	}
	cout << endl << "End." << endl;
	return 0;
}

// 执行Hash-Lock协议的测试
int Run_HL(const int tags[], size_t size){
	// 测试 Hash-Lock 协议
	cout << endl << "\tTest for Hash-Lock Protocol" << endl;
	TestHL test_hl;
	// 可能需要先测试数据是否正确、完整
	if (test_hl.InitData()){
		cout << endl << "Data initial succeed." << endl;
		cout << endl << "Test Starting..." << endl;
	}
	else{
		cout << endl << "Data initial failure." << endl;
		return -1;
	}

	cout << endl << "Result: \n" << endl;
	size_t i = 0, j = 0;
	LONGLONG lltime = 0;
	while (i < size){
		int tag = tags[i++];
		for (j = 0, lltime = 0; j < 10; ++j){
			lltime += test_hl.ProtocolFun(tag);
		}
		cout << "Tag" << i << " (" << tag << "):\t"
			<< "Time is " << lltime / 10 << " ns." << endl;
	}
	cout << endl << "End." << endl;

	return 0;
}

// 执行LAST协议的测试
int Run_L(const int tags[], size_t size){
	// 测试 LAST 协议
	cout << endl << "\tTest for LAST Protocol" << endl;

	TestLAST test_last;
	// 可能需要先测试数据是否正确、完整
	if (test_last.InitData()){
		cout << endl << "Data initial succeed." << endl;
		cout << endl << "Test Starting..." << endl;
	}
	else{
		cout << endl << "Data initial failure." << endl;
		return -1;
	}

	cout << endl << "Result: \n" << endl;
	size_t i = 0, j = 0;
	LONGLONG lltime = 0;
	while (i < size){
		int tag = tags[i++];
		for (j = 0, lltime = 0; j < 10; ++j){
			lltime += test_last.ProtocolFun(tag);
		}
		cout << "Tag" << i << " (" << tag << "):\t"
			<< "Time is " << lltime / 10 << " ns." << endl;
	}
	cout << endl << "End." << endl;
	return 0;
}