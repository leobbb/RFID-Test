// ���� LAST	 Э��

#include "stdafx.h"
#include "test_last.h"

using namespace std;

// �����ݿ��в�������
int TestLAST::InsertData(){

	hash<unint> int_hash;

	// ��ʼ�������ݿ�
	//ADOConn dbConn;
	try{
		// �����ݿ����������
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

// ���������Ƿ���ȷ
bool TestLAST::TestData(){
	string sql = "";

	//�������ݿ��м�¼���� 
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

// ��ʼ�����ݿ��е�����
bool TestLAST::InitData(){
	// ���������ȷ���򷵻�TRUE��
	if (TestData())
		return TRUE;

	// ��ʼ������
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


// ģ���ǩ��Ϊ�ĺ���
TestLAST::Response_Info TestLAST::TagFun(TestLAST::Request_Info req){

	// ��ȡ Request_Info�ڵ���Ϣ
	unint index, key, r1;
	index = req.index;
	key = req.key;
	r1 = req.r1;
	hash<unint> int_hash;		

	// ��������� r2
	unint r2 = _Random_device();
	
	// ����Hashֵ
	unint h = int_hash(r1&r2&key);	

	// ������Ӧ��Ϣ
	Response_Info res;			
	res.index = index;
	res.r2 = r2;
	res.v = h;

	return  res;
}

// ģ���Ķ�����Ϊ�ĺ���
TestLAST::Result_Info TestLAST::ReaderFun(Response_Info res, unint r1,Refresh_Info & refresh){
	// ��ȡ��Ӧ��Ϣ
	unint index, r2, v;
	index = res.index;
	r2 = res.r2;
	v = res.v;
	
	// ���ݿ��д洢�ı�ǩ��Կ, �µ�Hashֵ
	unint key, v1;		
	hash<unint> int_hash;		// ����Hashֵ

	string sql;
	sql = "select [Index],[Key] from [Tags_LAST] where [Index] = ";
	sql += itostr(index);
	_RecordsetPtr pRecordset = adoConn.GetRecordSet(sql.c_str());

	if (pRecordset->GetState() == adStateClosed || pRecordset->GetRecordCount() == 0)
		return FALSE;

	// ������¼�� ��������1����¼��
	key = pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();
	v1 = int_hash(r1&r2&key);

	if (v1 == v)
	{
		//cout << endl << "Test end." << endl;
		
		unint index1 = int_hash(r1&r2&index&key);	// ����õ���ǩ�µ�����ֵ
		unint key1 = int_hash(r1&r2&key);			// ����õ���ǩ�µ���Կ
		refresh = int_hash(r1&r2&key1);					// �õ�ˢ�±�ǩ����֤��Ϣ

		sql = "UPDATE [Tags_LAST] SET [Index] =	";
		sql += itostr(index1);
		sql += ", [Key] = ";
		sql += itostr(key1);
		sql += "  WHERE [Index]= ";
		sql += itostr(index);
		if (adoConn.ExecuteSQL(sql.c_str()))
		{
			// ˢ�³ɹ�
			return TRUE;
		}
	}
	return FALSE;
}

// ģ���ǩˢ�µĹ���
bool TestLAST::TagFun(Request_Info req, Response_Info res, Refresh_Info refresh){
	unint index = req.index;
	unint key = req.key;
	unint r1, r2;
	r1 = req.r1;
	r2 = res.r2;
	hash<unint> int_hash;		// ����Hashֵ

	unint index1 = int_hash(r1&r2&index&key);
	unint key1 = int_hash(r1&r2&key);
	unint refresh1 = int_hash(r1&r2&key1);

	if (refresh1 == refresh){
		// ͨ���Ϸ��Ķ�����֤��Ȼ��ˢ�±�ǩ��Ϣ
		index = index1;
		key = key1;
		return TRUE;
	}
	else{
		// �Ƿ���֤����ˢ�±�ǩ��Ϣ
		return FALSE;
	}
}


// ģ�⽻�����̵ĺ���
unsigned _int64 TestLAST::ProtocolFun(const int & tag){
	// ��ȡ��ѡ��ǩ����Ϣ
	string sql;
	sql = "select [Index], [Key] from Tags_LAST where Num=";
	sql.append(itostr(tag));
	adoConn.GetRecordSet(sql.c_str());
	if (adoConn.m_pRecordset->GetState() == adStateClosed || adoConn.m_pRecordset->GetRecordCount() == 0)
	{
		cout << endl << "Tag-" << tag << " isn't in DataBase." << endl;
		return 0;
	}

	// ���ɲ�ѯ��Ϣ
	Request_Info ri;
	ri.index = adoConn.m_pRecordset->GetCollect("Index").uintVal;
	ri.key = adoConn.m_pRecordset->GetCollect("Key").uintVal;
	adoConn.CloseRecordset();

	// ��ʱ��
	MyTimer timer;

	timer.Start();

	// ���������
	unint R1 = _Random_device();
	ri.r1 = R1;

	// ����ģ���ǩ�ĺ���
	Response_Info res = TagFun(ri);

	// ��ǩ����ˢ�µ���֤��Ϣ
	Refresh_Info refresh = 0;

	// ����ģ���Ķ����ĺ���
	Result_Info result = ReaderFun(res, R1, refresh);

	// ��֤ͨ���� ˢ�±�ǩ
	if (result){
		TagFun(ri, res, refresh);
	}

	// ��ʱ����ֹ
	timer.Stop();

	return  timer.GetTime();
}
