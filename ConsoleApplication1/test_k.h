// ����k������˽ģ��

#ifndef _test_k_h_
#define _test_k_h_

// ����k������˽ģ�͵���
class TestK{
private:
	int k;
public:
	TestK();
	TestK(int tmp);
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

	typedef unsigned char Result_Info;			// ��֤���

	// �����ݿ��в�������
	int DataInsert();

	Response_Info TagFun(Request_Info rInfo);				// ģ���ǩ��Ϊ�ĺ���
	Result_Info ReaderFun(Response_Info res, unint r1);	// ģ���Ķ�����Ϊ�ĺ���
	unsigned _int64 ProtocolFun();							// ģ�⽻�����̵ĺ���

};
#endif