// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
#include <string>
#include <vector>
#include <memory>
#include <codecvt>

using namespace std;

// stl �������뾯��
#pragma warning(disable:4251) 



// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "libzippp/libzippp.h"
#include "PPTXOfficeCore.h"

using namespace libzippp;

#pragma comment(lib, "libzippp.lib")
#pragma comment(lib, "zip.lib")
#pragma comment(lib, "zlib.lib")