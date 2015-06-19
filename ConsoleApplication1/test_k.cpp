// ����k������˽ģ��

#include "stdafx.h"

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
	//ADOConn dbConn;
	try{

		// �����ݿ����������
		ostringstream sql;
		unint count = 0;
		size_t quaId;
		cout << endl << "Start Insert Data...." << endl;
		cout << "k = " << k << endl;
		for (int i = 1000 / k; i > 0; --i){		// ��k���з���
			quaId = int_hash(_Random_device());	// ͬһ��ʹ����ͬ��׼��ʶ��
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

// ��ʼ�����ݿ��е�����
bool TestK::InitData(){
	cout << endl << "Delete All Data..." << endl;
	string sql = "";
	sql = "TRUNCATE TABLE [Tags]";
	if (adoConn.ExecuteSQL(sql.c_str()))
		cout << "\tOperating is done." << endl;
	else
		return FALSE;

	cout << endl << "Insert New Data..." << endl;
	if (DataInsert() == 1000)
		cout << "\tOperating is done." << endl;
	else
		return FALSE;

	return TRUE;
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
	//std::cout << std::endl << "Request_Info: " << req << endl;
	//std::cout << endl << "Start TagFun ..." << endl;	
	// ��ȡ Request_Info�ڵ���Ϣ
	unint quaId, key, r1;
	quaId = req.QuasiId;	
	key = req.key;
	r1 = req.r1;
	hash<unint> int_hash;		// ����Hashֵ

	// �����������ʹ��r1��key�Ĳ���Ϊ����
	minstd_rand0 minrand(r1&key);		
	unint r2 = minrand();

	//std::cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	//std::cout << "Key: " << key << endl;
	
	unint h = int_hash(r1&r2&key);	// ����Hashֵ
	//std::cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// ������Ӧ��Ϣ
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	//std::cout << endl << "Response_Info: " << res << endl;
	//std::cout << endl << "TagFun end." << endl;
	return  res;
}

// ģ���Ķ�����Ϊ�ĺ���
TestK::Result_Info TestK::ReaderFun(Response_Info res, unint r1){ 
	// ��ȡ��Ӧ��Ϣ
	unint qua, r2, h;
	qua = res.QuasiId;
	r2 = res.r2;
	h = res.h;
	unint key, h1;		// ���ݿ��д洢�ı�ǩ��Կ, �µ�Hashֵ
	hash<unint> int_hash;		// ����Hashֵ

	//cout << endl << "Start ReaderFun ... QuasiId = " << qua << endl;
	// �������ݿ�
	//ADOConn adoConn;
	string sql;
	sql = "select [QuasiId],[Key] from Tags where QuasiId = ";
	sql += itostr(qua);
	_RecordsetPtr pRecordset = adoConn.GetRecordSet(sql.c_str());
	
	if (pRecordset->GetRecordCount() == 0)
		return false;
	// ������¼��
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

// ģ�⽻�����̵ĺ���
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
	// ���ɲ�ѯ��Ϣ
	Request_Info ri;
	ri.QuasiId = adoConn.m_pRecordset->GetCollect("QuasiId").uintVal;
	ri.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;

	// ��ʱ��
	MyTimer timer;
	// ��ʼ�������������
	minstd_rand0 minrand(timer.GetBegin());

	timer.Start();

	// ���������
	//random_device rd;	
	unint R1 = minrand();

	//hash<string> str_hash;
	//unint qua = str_hash("QuasiID of Tag");
	//hash<unint> int_hash;
	//unint key = int_hash(qua&r1);

	ri.r1 = R1;

	// ����ģ���ǩ�ĺ���
	//std::cout << "TagFun()..." << endl;
	Response_Info res = TagFun(ri);

	// �����Ķ����ĺ���
	//std::cout << endl << "ReaderFun()..." << endl;
	Result_Info result = ReaderFun(res, R1);

	timer.Stop();			// ��ʱ����ֹ

	//cout << endl << "Result: " << endl;
	//if (result == TRUE)
	//	cout << "\tSuccess! Tag is authentication." << endl;
	//else cout << "\tFailure" << endl;
	//cout << endl << "Test end." << endl;

	return  timer.GetTime();
}

// ģ�⽻�����̵ĺ��� �޺�������
unsigned _int64 TestK::Protocol(const int & tag){
	string sql;
	sql = "select [QuasiId], [Key] from Tags where Id=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	//if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	//{
	//	cout << endl << "Tag[" << tag << "] isn't in DataBase." << endl;
	//	return 0;
	//}

	// ���ɲ�ѯ��Ϣ
	Request_Info req;
	req.QuasiId = adoConn.m_pRecordset->GetCollect("QuasiId").uintVal;
	req.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;

	// ��ʱ��
	MyTimer timer;	
	// ��ʼ�������������
	minstd_rand0 minrand(timer.GetBegin());

	timer.Start();

	// ���������
	//random_device rd;	
	unint R1 = minrand();
	req.r1 = R1;
	// ��ѯ��Ϣ���ɽ���
	// �رռ�¼��
	adoConn.CloseRecordset();

	// ����ģ���ǩ�ĺ���
	//std::cout << "TagFun()..." << endl;
	//Response_Info res = TagFun(req);

	// ��ȡ Request_Info�ڵ���Ϣ
	unint quaId, tkey, r1;
	quaId = req.QuasiId;
	tkey = req.key;
	r1 = req.r1;
	hash<unint> int_hash;		// ����Hashֵ

	// �����������ʹ��r1��key�Ĳ���Ϊ����
	minstd_rand0 minrand1(r1&tkey);
	unint R2 = minrand1();

	//std::cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	//std::cout << "Key: " << key << endl;

	unint h = int_hash(r1&R2&tkey);	// ����Hashֵ
	//std::cout << "hash(r1,r2,key): " << h << endl;
	
	// ������Ӧ��Ϣ
	Response_Info res;			
	res.QuasiId = quaId;
	res.r2= R2;
	res.h = h;
	// ��ǩ����Ϊ����

	// �����Ķ����ĺ���
	//std::cout << endl << "ReaderFun()..." << endl;
	//Result_Info result = ReaderFun(res, R1);

	// ��ȡ��Ӧ��Ϣ
	unint qua,rr1, tr2, th;
	qua = res.QuasiId;
	rr1 = R1;
	tr2 = res.r2;
	th = res.h;
	unint dbkey, h1;		// ���ݿ��д洢�ı�ǩ��Կ, �µ�Hashֵ

	//cout << endl << "Start ReaderFun ... QuasiId = " << qua << endl;
	// �������ݿ�
	//ADOConn adoConn;
	//string sql;
	sql = "select [QuasiId],[Key] from Tags where QuasiId = ";
	sql += itostr(qua);
	adoConn.GetRecordSet(sql.c_str());

	//if (adoConn.m_pRecordset->GetRecordCount() == 0)
	//	return false;
	// ������¼��
	while (adoConn.m_pRecordset->adoEOF == 0){
		dbkey = adoConn.m_pRecordset->GetCollect("Key").uintVal;
		h1 = int_hash(rr1&tr2&dbkey);
		if (h1 == th)
		{
			//cout << endl << "Test end." << endl;
			break;
		}
		adoConn.m_pRecordset->MoveNext();
	}

	//cout << endl << "ReaderFun end." << endl;
	// ��֤���̽���
	// ��ʱ����ֹ
	timer.Stop();			

	//cout << endl << "Result: " << endl;
	//if (result == TRUE)
	//	cout << "\tSuccess! Tag is authentication." << endl;
	//else cout << "\tFailure" << endl;
	//cout << endl << "Test end." << endl;

	return  timer.GetTime();
}