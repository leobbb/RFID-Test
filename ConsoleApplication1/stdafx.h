// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件
#include <iostream>
//#include "rfid_old.h"
#include <string>
#include <sstream>
#include <ctime>
#include "MyTimer.h"			// 计时器
#include <random>				// 随机数生成
#include <functional>			// 用到hash函数
#include "rfid.h"
#include "test_k.h"				// k-匿名模型
#include "ADOConn.h"			// 数据库连接
#include "test_hl.h"			// Hash-Lock协议
#include "test_last.h"			// LAST协议