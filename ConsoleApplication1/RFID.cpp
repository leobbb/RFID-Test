// RFID.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

using namespace std;

ADOConn adoConn;				// ���� ȫ�����ݿ����Ӷ���

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "\t Hello! Task Start... " << endl;
	try{
		// �������ݿ�����
		adoConn.OnInitADOConn();
		if (adoConn.m_pConnection != NULL && adoConn.m_pConnection->State == adStateOpen)
			cout << endl << "DB connection success." << endl;
		else{
			cout << endl << "DB connection failure." << endl;
			return -1;
		}

		// ���ѡȡ10����ǩ��Ϊʵ�����
		int tags[10];
		int i = 0;
		for (i = 0; i < 10; ++i){
			tags[i] = _Random_device() % 1000 + 1;  // ȡ1...1000֮�����
		}

		// ��ʵ������������ ProtocolFun ��������ʵ��
		// ���� k-����ģ��
		TestK test_k;
		cout << endl << "Result of k-anonymous: " << endl;

		while (i){
			// ������Ҫ�Ȳ��������Ƿ���ȷ������
			//test_k.DataInsert();
			int tag = tags[--i];
			LONGLONG lltime = 0;
			for (int j = 0; j < 10; ++j){
				lltime += test_k.ProtocolFun(tag);
			}
			cout << "Tag[" << tag << "]:\t"
				<< "Time is " << lltime / 10 << " ns." << endl;
		}
		
		cout << endl << "End." << endl;
	}
	catch (_com_error){

	}

	return 0;
}

// ��������ת��Ϊ�ַ���
string itostr(size_t i){		
	char buf[20];
	sprintf_s(buf, "%u", i);
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
