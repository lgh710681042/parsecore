// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
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


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "PptFileFormat.h"
#include "../SimpleStream/SimpleStreamHeaders.h"

// stl �������뾯��
#pragma warning(disable:4251) 

#ifdef _DEBUG
#pragma comment(lib, "SimpleStream_ud.lib")
#else
#pragma comment(lib, "SimpleStream_u.lib")
#endif