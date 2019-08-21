#include "stdafx.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "AbstractHeader.h"
#include "Header.h"
#include "AbstractFat.h"
#include "Fat.h"
#include "StructuredStorageReader.h"


StructuredStorageReader::StructuredStorageReader()
{
}


StructuredStorageReader::StructuredStorageReader(const wstring& fileName)
{
	_spFileHandler = make_shared<InputHandler>(fileName);

	//////////////////////////////////////////////////////////////////////////
	_spHeader = make_shared<Header>(_spFileHandler);
	// ������ȡ���������������á�ǿ�������⵼���ڴ��ͷű���
	_spFileHandler->SetHeaderReference(_spHeader);
	_spHeader->ReadHeader();
	//////////////////////////////////////////////////////////////////////////

	_spFat = make_shared<Fat>(_spHeader, _spFileHandler);
}

StructuredStorageReader::~StructuredStorageReader()
{
}
