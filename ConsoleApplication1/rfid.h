#ifndef _rfid_h_
#define _rfid_h_
#include <comdef.h>	
#include "ADOConn.h"

typedef unsigned int unint;		// �޷�������
extern ADOConn adoConn;				// ���� ȫ�����ݿ����Ӷ���

extern inline std::string itostr(size_t i);	// ��������ת��Ϊ�ַ���
inline unint strtoi(std::string s);		// ���ַ���ת��Ϊ������

extern void printerror(_com_error e);		// ����쳣��Ϣ
#endif