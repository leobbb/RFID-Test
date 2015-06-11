#ifndef _rfid_h_
#define _rfid_h_

struct Request_Info
{
	std::string QuasiId;  // 标签准标识符
	std::string key;		// 标签密钥
	int r1;					// 随机数
};

struct Response_Info
{
	std::string QuasiId;	// 标签准标识符
	int r2;					// 随机数
	int h;					// 哈希值
};

#endif