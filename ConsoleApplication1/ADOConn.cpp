// ADOConn.cpp: implementation of the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ADOConn::ADOConn()
{
	//��ʼ��OLE/COM�⻷��
	::CoInitialize(NULL);

	m_pConnection = NULL;
	m_pRecordset = NULL;
}

ADOConn::~ADOConn(){
	ExitConnect();
	m_pConnection = NULL;
	m_pRecordset = NULL;
	//�ͷŻ���
	::CoUninitialize();
}

void ADOConn::OnInitADOConn()
{

	try
	{
		//����connection����
       m_pConnection.CreateInstance("ADODB.Connection");

	   //���������ַ���
	   _bstr_t strConnect = "Provider=SQLOLEDB.1;Data Source=np:\\\\.\\pipe\\LOCALDB#218702CE\\tsql\\query;Integrated Security=SSPI;Persist Security Info=False;User ID=sa;Initial Catalog=rfid;";

	   //SERVER��UID,PWD�����ø���ʵ�����������
	   m_pConnection->Open(strConnect,"","",adModeUnknown);

	}
	//��׽�쳣
	catch(_com_error e)
	{
		m_pConnection = NULL;
		//��ʾ������Ϣ
		printerror(e);
	}
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
    try
	{
		//�������ݿ⣬���connection����Ϊ�ջ��߹رգ��������������ݿ�
		if (m_pConnection == NULL || m_pConnection->GetState() == adStateClosed)
			OnInitADOConn();

		//������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset)); 
		//ȡ�ñ��еļ�¼
        m_pRecordset->Open(bstrSQL,m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
    catch(_com_error e)
	{
		printerror(e);
	}
	//���ؼ�¼��
	
	return m_pRecordset;
}

// �رռ�¼��
void ADOConn::CloseRecordset(){
	if (m_pRecordset != NULL && m_pRecordset->GetState() == adStateOpen)
		m_pRecordset->Close();
}

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	_variant_t RecordsAffected;
	try
	{
		//�������ݿ⣬���connection����Ϊ�ջ��߹رգ��������������ݿ�
		if (m_pConnection == NULL || m_pConnection->GetState() == adStateClosed)
			OnInitADOConn();

		//connection�����Execute����(_bstr_t CommandText,
        //VARIANT * RecordsAffected,long Options)
		//����CommandText�������ַ���,ͨ����SQL����
		//����RecordsAffected�ǲ�����ɺ���Ӱ�������
		//����Options��ʾCommandText������,adCmdText-�ı�����,adCmdTable-����
		//adCmdProc-�洢����,adCmdUnknown-δ֪
        m_pConnection->Execute(bstrSQL,NULL,adCmdText);
		return true;
	}
	catch(_com_error e)
	{
		printerror(e);
		return false;
	}
}

void ADOConn::ExitConnect()
{
	try{
		//�رռ�¼��������
		if (m_pRecordset != NULL && m_pRecordset->GetState() == adStateOpen)
			m_pRecordset->Close();
		if (m_pConnection != NULL && m_pConnection->GetState() == adStateOpen)
			m_pConnection->Close();
	}
	catch (_com_error e){
		printerror(e);
	}
}