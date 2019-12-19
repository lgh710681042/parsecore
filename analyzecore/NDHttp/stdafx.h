// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>


#include "curl/curl.h"

#ifdef _DEBUG
#pragma comment(lib, "libcurld.lib")
#pragma comment(lib, "zdll_d.lib")
#else
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "zdll.lib")
#endif // DEBUG

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")

#include <tchar.h>
#include <string>
#include <mutex>          // std::mutex, std::unique_lock
#include <vector>
using namespace std;

#ifdef UNICODE
typedef wstring	tstring;
#else
typedef string	tstring;
#endif
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
