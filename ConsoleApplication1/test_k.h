// 测试k匿名隐私模型

#ifndef _test_k_h_
#define _test_k_h_

// 测试k匿名隐私模型的类
class TestK{
private:
	int k;
public:
	TestK();
	TestK(int tmp);
	
	// 获得参数k的值
	int GetK();

	struct Request_Info		// 查询信息
	{
		unsigned int QuasiId;  // 标签准标识符
		unsigned int key;		// 标签密钥
		unsigned int r1;		// 随机数
		friend std::ostream& operator <<(std::ostream& out, Request_Info value);
	};

	struct Response_Info	// 标签响应信息
	{
		unsigned int QuasiId;	// 标签准标识符
		unsigned int r2;			// 随机数
		unsigned int h;				// 哈希值

		friend std::ostream& operator<<(std::ostream& out, Response_Info value);
	};

	typedef bool Result_Info;			// 认证结果

	// 初始化数据库中的数据
	bool InitData();
	// 测试数据是否正确
	bool TestData();
	// 向数据库中插入数据
	int InsertData();

	Response_Info TagFun(Request_Info rInfo);				// 模拟标签行为的函数
	Result_Info ReaderFun(Response_Info res, unint r1);		// 模拟阅读器行为的函数
	unsigned _int64 ProtocolFun(const int& tag);			// 模拟交互过程的函数
	unsigned _int64 Protocol(const int & tag);				// 模拟交互过程的函数 无函数调用

};
#endif