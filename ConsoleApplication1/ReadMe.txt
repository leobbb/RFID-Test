========================================================================
    控制台应用程序：RFID 项目概述
========================================================================

应用程序向导已为您创建了此 ConsoleApplication1 应用程序。

本文件概要介绍组成 ConsoleApplication1 应用程序的每个文件的内容。


ConsoleApplication1.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

ConsoleApplication1.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

ConsoleApplication1.cpp
    这是主应用程序源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 ConsoleApplication1.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

ADOConn.h ADOConn.cpp 
	这些文件封装了对数据库的操作，并且程序在 rfid.h 中声明了一个全局变量 “adoConn”,用于操作数据库。

rfid.h RFID.cpp 
	该文件是进行实验的主文件，包含程序的入口。并且具有一些公共函数。

MyTimer.h Timer.cpp
	封装了对时间的操作，用于计算程序运行的时间。

test_k.h test_k.cpp 
	拥有用于对k匿名隐私模型进行模拟的类。

test_hl.h test_hl.cpp
	拥有用于对Hash-Lock协议进行模拟的类。

test_last.h test_last.cpp
	拥有用于对LAST协议进行模拟的类。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。


数据库使用的 SQL Server LocalDB, 在文件“ADOConn.cpp”中的链接字符串“strConnect”里 “Data Source”使用的 LocalDB 的“实例管道名称”，比如
	Data Source=np:\\\\.\\pipe\\LOCALDB#3C61E53E\\tsql\\query；
LocalDB 的实例重新启动之后，“实例管道名称”都很发生改变，需要重新进行设置。 
这个值在文件“ADOConn.cpp”中进行修改。

数据库名称为“rfid”， 数据表分别为：Tags_K，Tags_HL，Tags_LAST。
一下是创建数据表的SQL语句。

K-匿名模型
CREATE TABLE [dbo].[Tags_K] (
    [Num]     INT    IDENTITY (1, 1) NOT NULL,
    [QuasiId] BIGINT NOT NULL,
    [Key]     BIGINT NOT NULL,
    CONSTRAINT [PK_Tags_K] PRIMARY KEY CLUSTERED ([Num] ASC)
);

Hash-Lock协议模型
CREATE TABLE [dbo].[Tags_HL] (
    [Num] INT    IDENTITY (1, 1) NOT NULL,
    [Id]  BIGINT NOT NULL,
    [Key] BIGINT NOT NULL,
    CONSTRAINT [PK_Tags_HL] PRIMARY KEY CLUSTERED ([Num] ASC)
);

LAST协议模型
CREATE TABLE [dbo].[Tags_LAST] (
    [Num]   INT    IDENTITY (1, 1) NOT NULL,
    [Index] BIGINT NOT NULL,
    [Key]   BIGINT NOT NULL,
    CONSTRAINT [PK_Tags_LAST] PRIMARY KEY CLUSTERED ([Num] ASC)
);


/////////////////////////////////////////////////////////////////////////////
