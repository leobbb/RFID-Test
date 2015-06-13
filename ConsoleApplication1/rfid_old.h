#ifndef _rfid_old_h_
#define _rfid_old_h_

struct Request_Info		// ��ѯ��Ϣ
{
	unsigned int QuasiId;  // ��ǩ׼��ʶ��
	unsigned int key;		// ��ǩ��Կ
	unsigned int r1;		// �����

	friend std::ostream& operator <<(std::ostream& out, Request_Info value);
};

struct Response_Info	// ��ǩ��Ӧ��Ϣ
{
	unsigned int QuasiId;	// ��ǩ׼��ʶ��
	unsigned int r2;			// �����
	unsigned int h;				// ��ϣֵ

	friend std::ostream& operator<<(std::ostream& out, Response_Info value);
};

//typedef std::string Request_Info;	// ��ѯ��Ϣ
//typedef std::string Response_Info;	// ��ǩ��Ӧ��Ϣ
typedef unsigned char Result_Info;			// ��֤���

inline std::string itostr(size_t i);	// ��������ת��Ϊ�ַ���
inline unsigned int strtoi(std::string s);		// ���ַ���ת��Ϊ������

Response_Info TagFun(Request_Info rInfo);	// ģ���ǩ��Ϊ�ĺ���
Result_Info ReaderFun(Response_Info, std::string r1); // ģ���Ķ�����Ϊ�ĺ���
unsigned _int64 ProtocolFun();			// ģ�⽻�����̵ĺ���

#endif