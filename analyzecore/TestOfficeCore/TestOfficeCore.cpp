// TestOfficeCore.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	shared_ptr<CNDPowerpointDoc> spDoc = make_shared<CNDPowerpointDoc>();
	spDoc->OpenDoc(_T("F:\\ppttest\\1.ppt"));

	std::vector<shared_ptr<CNDSlide>> vecSlides = spDoc->GetSlides();
	return 0;
}

