// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <memory>
#include <string>
#include <assert.h>
#include <locale>
#include <codecvt>
#include <set>
#include <vector>
#include <stack>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "types.h"
#include "macros.h"

#include "libxml/xmlstring.h"
#include "libxml/parser.h"

#include "OdfOfficeCore.h"

#ifdef _DEBUG
#pragma comment(lib, "libxml2.lib")
#else
#endif // DEBUG


using namespace std;