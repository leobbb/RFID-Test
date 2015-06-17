// RFID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

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
	cout << endl << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// 调用阅读器的函数
	cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, r1);

	timer.Stop();			// 计时器终止
	cout << "Time of process: " << timer.GetTime() << endl;
	
	cout << endl << "Result: " << endl;
	if (result == '1')
		cout << "Success" << endl;
	else cout << "Failure" << endl;
	
	ADOConn dbConn;
	dbConn.OnInitADOConn();
	if (dbConn.m_pConnection != NULL && dbConn.m_pConnection->State == adStateOpen)
		cout << endl << "DB connection success." << endl;
	else
		cout << endl << "DB connection failure." << endl;
	
	_bstr_t sqlInsert = "insert into Tags values (1221,1212)";
	dbConn.ExecuteSQL(sqlInsert);

	dbConn.ExitConnect();

	//::CoInitialize(NULL);		// 初始化OLE/COM	库环境
	//_ConnectionPtr pMyConn = NULL;
	//HRESULT hr = pMyConn.CreateInstance("ADODB.Connection");

	//_bstr_t strConn = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;User ID=sa;Initial Catalog=rfid;Data Source=np:\\\\.\\pipe\\LOCALDB#SH9F91AA\\tsql\\query;";
	//try{
	//	cout << "in try---" << endl;
	//	pMyConn->Open(strConn, "", "", adModeUnknown);
	//	cout << endl << "open success." << endl;
	//}
	//catch (_com_error &e){
	//	printf("\tcode = %010lx\n", e.Error());
	//	printf("\tcode meaning = %s \n", e.ErrorMessage());
	//	cout << "exception " << endl;
	//}

	//cout << "end" << endl;
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