#ifndef _rfid_old_h_
#define _rfid_old_h_

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

//typedef std::string Request_Info;	// 查询信息
//typedef std::string Response_Info;	// 标签响应信息
typedef unsigned char Result_Info;			// 认证结果

inline std::string itostr(size_t i);	// 将整形数转换为字符串
inline unsigned int strtoi(std::string s);		// 将字符串转换为整形数

Response_Info TagFun(Request_Info rInfo);	// 模拟标签行为的函数
Result_Info ReaderFun(Response_Info, std::string r1); // 模拟阅读器行为的函数
unsigned _int64 ProtocolFun();			// 模拟交互过程的函数

#endif