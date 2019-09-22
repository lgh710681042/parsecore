#pragma once

class PptFileFormat_API ClientData
	: public Record
{
public:
	ClientData();
	ClientData(shared_ptr<BinaryReader> spBinaryReader,
		unsigned long size,
		unsigned long typeCode,
		unsigned int version,
		unsigned int instance);
	virtual ~ClientData();

public:
	unsigned char* bytes = nullptr;
	//  public Dictionary<AnimationInfoContainer, int> animinfos = new Dictionary<AnimationInfoContainer, int>();
	// ʹ��vector�洢����shape��AnimationInfoContainer
	vector<shared_ptr<AnimationInfoContainer>> m_vecAnimInfoContainer;
};
