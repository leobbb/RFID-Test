#ifndef _rfid_h_
#define _rfid_h_
#include <comdef.h>	
#include "ADOConn.h"

typedef unsigned int unint;		// 无符号整形
extern ADOConn adoConn;				// 声明 全局数据库连接对象

extern inline std::string itostr(size_t i);	// 将整形数转换为字符串
inline unint strtoi(std::string s);		// 将字符串转换为整形数

extern void printerror(_com_error e);		// 输出异常信息

int Run_K(const int tags[], size_t size);	// 执行k-匿名模型的测试
int Run_HL(const int tags[], size_t size);	// 执行Hash-Lock协议的测试
int Run_L(const int tags[], size_t size);	// 执行LAST协议的测试

#endif