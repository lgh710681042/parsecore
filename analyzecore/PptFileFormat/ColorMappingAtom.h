#pragma once

class PptFileFormat_API ColorMappingAtom
	: public XmlStringAtom
{
public:
	ColorMappingAtom();
	ColorMappingAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~ColorMappingAtom();
};

