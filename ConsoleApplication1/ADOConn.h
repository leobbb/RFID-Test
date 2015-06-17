// ADOConn.h: interface for the ADOConn class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _adoconn_h_
#define _adoconn_h_
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")


class ADOConn  
{
public:
	//添加一个指向Connection对象的指针
    _ConnectionPtr m_pConnection;
	//添加一个指向Recordset对象的指针
	_RecordsetPtr m_pRecordset;

public:
	ADOConn();

	//初始化--连接数据库
    void OnInitADOConn();
	//执行查询
    _RecordsetPtr & GetRecordSet(_bstr_t bstrSQL);
	// 关闭记录集
	void ADOConn::CloseRecordset();
	//执行SQL语句
    BOOL ExecuteSQL(_bstr_t bstrSQL);
	//断开数据库连接
	void ExitConnect();
};

#endif // !define _adoconn_h_
