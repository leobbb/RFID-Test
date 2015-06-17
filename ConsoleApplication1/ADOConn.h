// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _adoconn_h_
#define _adoconn_h_
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")


class ADOConn  
{
public:
	//���һ��ָ��Connection�����ָ��
    _ConnectionPtr m_pConnection;
	//���һ��ָ��Recordset�����ָ��
	_RecordsetPtr m_pRecordset;

public:
	ADOConn();

	//��ʼ��--�������ݿ�
    void OnInitADOConn();
	//ִ�в�ѯ
    _RecordsetPtr & GetRecordSet(_bstr_t bstrSQL);
	// �رռ�¼��
	void ADOConn::CloseRecordset();
	//ִ��SQL���
    BOOL ExecuteSQL(_bstr_t bstrSQL);
	//�Ͽ����ݿ�����
	void ExitConnect();
};

#endif // !define _adoconn_h_
