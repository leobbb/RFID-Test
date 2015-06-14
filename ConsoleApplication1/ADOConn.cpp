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
	m_pConnection = NULL;
	m_pRecordset = NULL;
}

ADOConn::~ADOConn()
{

}

void ADOConn::OnInitADOConn()
{
	//��ʼ��OLE/COM�⻷��
    ::CoInitialize(NULL);
	try
	{
		//����connection����
       m_pConnection.CreateInstance("ADODB.Connection");

	   //���������ַ���
	   _bstr_t strConnect = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;User ID=sa;Initial Catalog=rfid;Data Source=np:\\\\.\\pipe\\LOCALDB#SH9F91AA\\tsql\\query;";

	   //SERVER��UID,PWD�����ø���ʵ�����������
	   m_pConnection->Open(strConnect,"","",adModeUnknown);

	}
	//��׽�쳣
	catch(_com_error e)
	{
		//��ʾ������Ϣ
		printerror(e);
	}
}

_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL)
{
    try
	{
		//�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
		if(m_pConnection==NULL)
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

BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	_variant_t RecordsAffected;
	try
	{
		//�Ƿ����������ݿ�
        if(m_pConnection==NULL)
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
		if (m_pRecordset != NULL)
			m_pRecordset->Close();
		if (m_pConnection != NULL)
			m_pConnection->Close();
		//�ͷŻ���
		::CoUninitialize();
	}
	catch (_com_error e){
		printerror(e);
	}
}