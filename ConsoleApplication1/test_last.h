// ���� LAST Э��

#ifndef _test_last_h_
#define _test_last_h_

// ���� LAST Э�����
class TestLAST{

public:

	struct Request_Info		// ��ѯ��Ϣ
	{
		unsigned int index;		// ��ǩ����ֵ
		unsigned int key;		// ��ǩ��Կ
		unsigned int r1;		// �����
	};

	struct Response_Info	// ��ǩ��Ӧ��Ϣ
	{
		unsigned int index;		// ��ǩ����ֵ
		unsigned int r2;		// �����
		unsigned int v;			// ��ϣֵ
	};

	typedef bool Result_Info;		// ��֤���

	typedef unint Refresh_Info;		// ��ǩ����ˢ�µ���֤��Ϣ

	// ��ʼ�����ݿ��е�����
	bool InitData();
	// ���������Ƿ���ȷ
	bool TestData();
	// �����ݿ��в�������
	int InsertData();

	Response_Info TagFun(Request_Info);						// ģ���ǩ��Ӧ�Ĺ���
	Result_Info ReaderFun(Response_Info res, unint r1, Refresh_Info & ref);		// ģ���Ķ�����Ϊ�ĺ���,ref �������Ϣ ������ǩ��ˢ��
	bool TagFun(Request_Info, Response_Info, Refresh_Info);						// ģ���ǩˢ�µĹ���

	unsigned _int64 ProtocolFun(const int& tag);			// ģ�⽻�����̵ĺ���

};

#endif