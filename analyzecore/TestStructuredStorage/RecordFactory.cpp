#include "stdafx.h"
#include "Singleton.h"
#include "Common.h"
#include "GlobalDefines.h"
#include "SimpleBinStream.h"
#include "InternalBitConverter.h"
#include "AbstractHeader.h"
#include "AbstractIOHandler.h"
#include "InputHandler.h"
#include "Header.h"
#include "AbstractFat.h"
#include "BaseStream.h"
#include "VirtualStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "CurrentUserAtom.h"
#include "UserEditAtom.h"
#include "PersistDirectoryEntry.h"
#include "PersistDirectoryAtom.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"
#include "GPointAtom.h"
#include "GRatioAtom.h"
#include "DocumentAtom.h"
#include "Environment.h"
#include "UnknownRecord.h"
#include "FontEntityAtom.h"
#include "FontCollection.h"
#include "TabStop.h"
#include "GrColorAtom.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "TextCFExceptionAtom.h"
#include "TextPFExceptionAtom.h"
#include "TextStyleAtom.h"
#include "TextMasterStyleAtom.h"
#include "PPDrawingGroup.h"
#include "DrawingGroup.h"
#include "FileIdCluster.h"
#include "DrawingGroupRecord.h"
#include "BitmapBlip.h"

#include "RecordFactory.h"


RecordFactory::RecordFactory()
{
}


RecordFactory::~RecordFactory()
{
}

std::shared_ptr<Record> RecordFactory::CreateRecord(shared_ptr<BaseStream> spBaseStream)
{
	return CreateRecord(make_shared<BinaryReader>(spBaseStream));
}

std::shared_ptr<Record> RecordFactory::CreateRecord(shared_ptr<BinaryReader> spBinaryReader)
{
	unsigned short verAndInstance = spBinaryReader->ReadUInt16();
	// first 4 bit of field verAndInstance
	unsigned long version = verAndInstance & 0x000FU;
	// last 12 bit of field verAndInstance
	unsigned long instance = (verAndInstance & 0x000FU) >> 4;

	unsigned short typeCode = spBinaryReader->ReadUInt16();
	unsigned long size = spBinaryReader->ReadUInt32();

	bool isContainer = (version == 0xF);
	shared_ptr<Record> spRecord = nullptr;

	switch (typeCode)
	{
	case PPT_PST_Document:
	{
		spRecord = make_shared<DocumentContainer>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_DocumentAtom:
	{
		spRecord = make_shared<DocumentAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_Environment:
	{
		spRecord = make_shared<Environment>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_PPDrawingGroup:
	{
		spRecord = make_shared<PPDrawingGroup>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_FontCollection:
	{
		spRecord = make_shared<FontCollection>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxMasterStyleAtom:
	{
		spRecord = make_shared<TextMasterStyleAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxCFStyleAtom:
	{
		spRecord = make_shared<TextCFExceptionAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_TxPFStyleAtom:
	{
		spRecord = make_shared<TextPFExceptionAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_FontEntityAtom:
	{
		spRecord = make_shared<FontEntityAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_UserEditAtom:
	{
		spRecord = make_shared<UserEditAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case PPT_PST_CurrentUserAtom:
	{
		spRecord = make_shared<CurrentUserAtom>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case PPT_PST_PersistPtrIncrementalBlock:
	{
		spRecord = make_shared<PersistDirectoryAtom>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	case DFF_msofbtDggContainer:
	{
		spRecord = make_shared<DrawingGroup>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case DFF_msofbtDgg:
	{
		spRecord = make_shared<DrawingGroupRecord>(spBinaryReader, size, typeCode, version, instance);
	}
	break;
	case DFF_msofbtBitmapBlip_1E:
	case DFF_msofbtBitmapBlip_1D:
	case DFF_msofbtBitmapBlip_1F:
	case DFF_msofbtBitmapBlip_20:
	{
		spRecord = make_shared<BitmapBlip>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	break;
	default:
	{
		spRecord = make_shared<UnknownRecord>(spBinaryReader, size, typeCode, version, instance);
	}
		break;
	}

	return spRecord;
}
