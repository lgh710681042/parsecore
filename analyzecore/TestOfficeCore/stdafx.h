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


using namespace std;

#pragma warning(disable:4251) 


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

#include "../OfficeCore/OfficeCore.h"
#include "../OfficeCore/NDSlide.h"
#include "../OfficeCore/NDPowerpointDoc.h"

#ifdef _DEBUG
#pragma comment(lib, "OfficeCore_ud.lib")
#else
#pragma comment(lib, "OfficeCore_u.lib")
#endif