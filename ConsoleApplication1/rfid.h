#ifndef _rfid_h_
#define _rfid_h_

struct Request_Info
{
	std::string QuasiId;  // ��ǩ׼��ʶ��
	std::string key;		// ��ǩ��Կ
	int r1;					// �����
};

struct Response_Info
{
	std::string QuasiId;	// ��ǩ׼��ʶ��
	int r2;					// �����
	int h;					// ��ϣֵ
};

#endif