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
#include <vector>

#include <string>
#include <tchar.h>


using namespace std;

// stl �������뾯��
#pragma warning(disable:4251) 


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "OfficeCore.h"
#include "../SimpleStream/SimpleStreamHeaders.h"
#include "../PptFileFormat/PptFileFormat.h"
#include "../PptFileFormat/PptFileFormatHeaders.h"



#ifdef _DEBUG
#pragma comment(lib, "PptFileFormat_ud.lib")
#else
#pragma comment(lib, "PptFileFormat_u.lib")
#endif