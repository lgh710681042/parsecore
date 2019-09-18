#include "stdafx.h"
#include "BaseStream.h"
#include "FileStream.h"


FileStream::FileStream()
{
}


FileStream::FileStream(const wstring& fileName)
{
	_spStream = make_shared<simple::file_ostream>(fileName.c_str());
}

FileStream::~FileStream()
{
	//����ֱ���ͷ�_spStream, �ļ�ֱ��close
}

size_t FileStream::Write(const unsigned char* p, size_t size)
{
	if (_spStream == nullptr)
		return 0;

	return _spStream->write(p, size);
}

size_t FileStream::Write(const char* p, size_t size)
{
	if (_spStream == nullptr)
		return 0;

	_spStream->write(p, size);

	//TODO:����ֵ
	return 0;
}

bool FileStream::Close()
{
	if (_spStream == nullptr)
		return false;

	_spStream->close();

	return true;
}
