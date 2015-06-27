// ���� Hash-Lock Э��

#ifndef _test_hl_h_
#define _test_hl_h_

// ���� Hash-Lock Э�����
class TestHL{

public:

	struct Request_Info		// ��ѯ��Ϣ
	{
		unsigned int id;		// ��ǩId
		unsigned int key;		// ��ǩ��Կ
	};

	struct Response_Info	// ��ǩ��Ӧ��Ϣ
	{
		unsigned int r;			// �����
		unsigned int h;			// ��ϣֵ
	};

	typedef bool Result_Info;			// ��֤���

	// ��ʼ�����ݿ��е�����
	bool InitData();
	// ���������Ƿ���ȷ
	bool TestData();
	// �����ݿ��в�������
	int InsertData();

	Response_Info TagFun(Request_Info);				// ģ���ǩ��Ϊ�ĺ���
	Result_Info ReaderFun(Response_Info res);		// ģ���Ķ�����Ϊ�ĺ���
	unsigned _int64 ProtocolFun(const int& tag);			// ģ�⽻�����̵ĺ���
	unsigned _int64 Protocol(const int & tag);				// ģ�⽻�����̵ĺ��� �޺�������

	void Run(int tags[]);							// ��ʼʵ��
};
#endif