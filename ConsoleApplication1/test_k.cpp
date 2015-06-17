// ����k������˽ģ��

#include "stdafx.h"
#include "test_k.h" 
using namespace std;

// Ĭ������� k = 5
TestK::TestK(){
	k = 5;
}

TestK::TestK(int tmp){
	k = tmp;
}

// �����ݿ��в�������
int TestK::DataInsert(){

	hash<unint> int_hash;

	// ��ʼ�������ݿ�
	ADOConn dbConn;
	try{
		dbConn.OnInitADOConn();
		if (dbConn.m_pConnection != NULL && dbConn.m_pConnection->State == adStateOpen)
			cout << endl << "DB connection success." << endl;
		else{
			cout << endl << "DB connection failure." << endl;
			return 2;
		}
		// �����ݿ����������
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


std::ostream& operator<<(ostream & out, TestK::Request_Info value){		// ��� ��ѯ��Ϣ
	out << value.QuasiId << " " << value.key << " " << value.r1;
	return out;
}

std::ostream& operator<<(ostream & out, TestK::Response_Info value){		// ��� ��Ӧ��Ϣ
	out << value.QuasiId << " " << value.r2 << " " << value.h;
	return out;
}

// ģ���ǩ��Ϊ�ĺ���
TestK::Response_Info TestK::TagFun(TestK::Request_Info req){

	std::cout << std::endl << "Request_Info: " << req << endl;

	unint quaId, key, r1;
	quaId = req.QuasiId;	// ��ȡ Request_Info�ڵ���Ϣ
	key = req.key;
	r1 = req.r1;

	minstd_rand0 minrand(r1&key);		// �����������ʹ��r1��key�Ĳ���Ϊ����
	unsigned int r2 = minrand();

	std::cout << endl << "TagFun Start ----" << endl;
	std::cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	std::cout << "Key: " << key << endl;

	hash<unsigned int > int_hash;		// ����Hashֵ
	unsigned int h = int_hash(r1&r2&key);
	std::cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// ������Ӧ��Ϣ
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	std::cout << endl << "Response_Info: " << res << endl;

	return  res;
}

// ģ���Ķ�����Ϊ�ĺ���
TestK::Result_Info TestK::ReaderFun(Response_Info res, unint r1){ 
	// ��ȡ��Ӧ��Ϣ
	unint qua, r2, h;
	qua = res.QuasiId;
	r2 = res.r2;
	h = res.h;

	// �������ݿ�
	unint key2 = 12345;		// ���ݿ��д洢�ı�ǩ��key
	hash<unint> int_hash;
	unint h1 = int_hash(r1&r2&key2);

	if (h1 == h)
		return '1';

	return '0';
}

// ģ�⽻�����̵ĺ���
unsigned _int64 TestK::ProtocolFun(){
	MyTimer timer;

	timer.Start();

	random_device rd;	// ���������
	unint r1 = rd();

	hash<string> str_hash;
	unint qua = str_hash("QuasiID of Tag");

	hash<unint> int_hash;
	unint key = int_hash(qua&r1);

	Request_Info ri;		// ���ɲ�ѯ��Ϣ
	ri.QuasiId = qua;
	ri.key = key;
	ri.r1 = r1;

	// ����ģ���ǩ�ĺ���
	std::cout << endl << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// �����Ķ����ĺ���
	std::cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, r1);

	timer.Stop();			// ��ʱ����ֹ
	cout << "Time of process: " << timer.GetTime() << endl;

	cout << endl << "Result: " << endl;
	if (result == '1')
		cout << "Success" << endl;
	else cout << "Failure" << endl;

	return 1;
}