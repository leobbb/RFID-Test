// RFID.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

	TestK test_k;
	test_k.DataInsert();

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

// 将整形数转换为字符串
string itostr(size_t i){		
	char buf[20];
	sprintf_s(buf, "%010.10u", i);
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
