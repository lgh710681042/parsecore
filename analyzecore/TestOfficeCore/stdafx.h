// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <memory>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

#pragma warning(disable:4251) 


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include "../SimpleStream/SimpleStreamHeaders.h"
#include "../PptFileFormat/PptFileFormat.h"
#include "../PptFileFormat/PptFileFormatHeaders.h"
#include "../OfficeCore/OfficeCoreHeaders.h"
#include "../PPTXOfficeCore/PPTXOfficeCoreHeaders.h"

#ifdef _DEBUG
#pragma comment(lib, "OfficeCore_ud.lib")
#pragma comment(lib, "PPTXOfficeCore_ud.lib")
#pragma comment(lib, "libxml2.lib")
#else
#pragma comment(lib, "OfficeCore_u.lib")
#pragma comment(lib, "PPTXOfficeCore_u.lib")
#pragma comment(lib, "libxml2.lib")
#endif