// RFID.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;

	TestK test_k;
	test_k.DataInsert();

	//::CoInitialize(NULL);		// ��ʼ��OLE/COM	�⻷��
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

// ��������ת��Ϊ�ַ���
string itostr(size_t i){		
	char buf[20];
	sprintf_s(buf, "%010.10u", i);
	return buf;
}

// ���ַ���ת��Ϊ������
unint strtoi(string s){		
	int i = atoi(s.c_str());
	return i;
}

// ����쳣��Ϣ
void printerror(_com_error e){	// ����쳣��Ϣ
	//��ʾ������Ϣ
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());

	printf("Error\n");
	printf("\tCode = %08lx\n", e.Error());
	printf("\tCode meaning = %s\n", e.ErrorMessage());
	printf("\tSource = %s\n", (LPCSTR)bstrSource);
	printf("\tDescription = %s\n", (LPCSTR)bstrDescription);

}
