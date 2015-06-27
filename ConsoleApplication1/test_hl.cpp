// ���� Hash-Lock ��˽ģ��

#include "stdafx.h"
#include "test_hl.h"

using namespace std;

// ��ʼ�����ݿ��е�����
bool TestHL::InitData(){
	// ���������ȷ���򷵻�TRUE��
	if (TestData())
		return TRUE;

	// ��ʼ������
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

	//�������ݿ��м�¼���� 
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

// �����ݿ��в�������
int TestHL::InsertData(){

	hash<unint> int_hash;

	// ��ʼ�������ݿ�
	//ADOConn dbConn;
	try{

		// �����ݿ����������
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


// ģ���ǩ��Ϊ�ĺ���
TestHL::Response_Info TestHL::TagFun(TestHL::Request_Info req){
	// ��ȡ��ǩ����Ϣ
	unint id, key;
	id = req.id;
	key = req.key;

	// ���������
	random_device rd;
	unint r = rd();

	// ����hashֵ
	hash<unint> int_hash; 
	unint h = int_hash(id&r);

	// ������Ӧ��Ϣ
	Response_Info res;
	res.r = r;
	res.h = h;
	
	return res;
}

// ģ���Ķ�����Ϊ�ĺ���
TestHL::Result_Info TestHL::ReaderFun(TestHL::Response_Info res){
	unint r, h;
	r = res.r;
	h = res.h;

	// ���ݿ��д洢�ı�ǩId
	unint id, h1; 
	hash<unint> int_hash;

	// �����ѯ�ַ�������ȡ���Եı�ǩ��Ϣ
	string sql;
	sql = "select [Id],[Key] from Tags_HL";
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pConnection->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
		return FALSE;
	
	// ���������
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

// ģ�⽻�����̵ĺ���
unsigned _int64 TestHL::ProtocolFun(const int& tag){
	// ��ȡ��ѡ��ǩ����Ϣ
	string sql;
	sql = "select [Id], [Key] from Tags_HL where Num=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	{
		cout << endl << "Tag[" << tag << "] isn't in DataBase." << endl;
		return 0;
	}

	// ���ɲ�ѯ��Ϣ
	Request_Info req;
	req.id= adoConn.m_pRecordset->GetCollect("Id").uintVal;
	req.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();

	// ��ʱ��
	MyTimer timer;
	// ��ʼ�������������
	minstd_rand0 minrand(timer.GetBegin());

	timer.Start();

	// ����ģ���ǩ�ĺ���
	Response_Info res = TagFun(req);

	// �����Ķ����ĺ���
	Result_Info result = ReaderFun(res);

	// ��ʱ����ֹ
	timer.Stop();

	return  timer.GetTime();

}