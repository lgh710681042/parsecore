#pragma once
class Record
{
public:
	Record();
	Record(shared_ptr<VirtualStream> spVirtualStream,
		unsigned long bodySize,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~Record();

	virtual wstring ToString(unsigned long depth);

public:
	unsigned long BodySize;
	unsigned long TypeCode;
	unsigned long Version;
	unsigned long Instance;

	unsigned char* RawData;
};
