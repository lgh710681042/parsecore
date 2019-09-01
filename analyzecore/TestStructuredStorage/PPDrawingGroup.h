#pragma once
class PPDrawingGroup 
	: public RegularContainer
{
public:
	PPDrawingGroup();
	PPDrawingGroup(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	~PPDrawingGroup();
};

