#ifndef _rfid_h_
#define _rfid_h_
#include <comdef.h>	

typedef unsigned int unint;		// �޷�������

inline std::string itostr(size_t i);	// ��������ת��Ϊ�ַ���
inline unint strtoi(std::string s);		// ���ַ���ת��Ϊ������

void printerror(_com_error e);		// ����쳣��Ϣ
#endif