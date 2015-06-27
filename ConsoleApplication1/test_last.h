// 测试 LAST 协议

#ifndef _test_last_h_
#define _test_last_h_

// 测试 LAST 协议的类
class TestLAST{

public:

	struct Request_Info		// 查询信息
	{
		unsigned int index;		// 标签索引值
		unsigned int key;		// 标签密钥
		unsigned int r1;		// 随机数
	};

	struct Response_Info	// 标签响应信息
	{
		unsigned int index;		// 标签索引值
		unsigned int r2;		// 随机数
		unsigned int v;			// 哈希值
	};

	typedef bool Result_Info;		// 认证结果

	typedef unint Refresh_Info;		// 标签用于刷新的验证信息

	// 初始化数据库中的数据
	bool InitData();
	// 测试数据是否正确
	bool TestData();
	// 向数据库中插入数据
	int InsertData();

	Response_Info TagFun(Request_Info);						// 模拟标签响应的过程
	Result_Info ReaderFun(Response_Info res, unint r1, Refresh_Info & ref);		// 模拟阅读器行为的函数,ref 是输出信息 用作标签的刷新
	bool TagFun(Request_Info, Response_Info, Refresh_Info);						// 模拟标签刷新的过程

	unsigned _int64 ProtocolFun(const int& tag);			// 模拟交互过程的函数

};

#endif