// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;


// TODO:  在此处引用程序需要的其他头文件
#include "PptFileFormat.h"
#include "../SimpleStream/SimpleStreamHeaders.h"

// stl 导出编译警告
#pragma warning(disable:4251) 

#ifdef _DEBUG
#pragma comment(lib, "SimpleStream_ud.lib")
#else
#pragma comment(lib, "SimpleStream_u.lib")
#endif