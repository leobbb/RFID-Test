// 测试 Hash-Lock 协议

#ifndef _test_hl_h_
#define _test_hl_h_

// 测试 Hash-Lock 协议的类
class TestHL{

public:

	struct Request_Info		// 查询信息
	{
		unsigned int id;		// 标签Id
		unsigned int key;		// 标签密钥
	};

	struct Response_Info	// 标签响应信息
	{
		unsigned int r;			// 随机数
		unsigned int h;			// 哈希值
	};

	typedef bool Result_Info;			// 认证结果

	// 初始化数据库中的数据
	bool InitData();
	// 测试数据是否正确
	bool TestData();
	// 向数据库中插入数据
	int InsertData();

	Response_Info TagFun(Request_Info);				// 模拟标签行为的函数
	Result_Info ReaderFun(Response_Info res);		// 模拟阅读器行为的函数
	unsigned _int64 ProtocolFun(const int& tag);			// 模拟交互过程的函数
	unsigned _int64 Protocol(const int & tag);				// 模拟交互过程的函数 无函数调用

	void Run(int tags[]);							// 开始实验
};
#endif