#pragma once

struct MasterTextPropRun
{
	unsigned long count;
	unsigned short indentLevel;
};

class MasterTextPropAtom 
	: public Record
{
public:
	MasterTextPropAtom();
	MasterTextPropAtom(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
 	virtual ~MasterTextPropAtom();

public:
	vector<MasterTextPropRun> m_vecMasterTextPropRuns;
};

