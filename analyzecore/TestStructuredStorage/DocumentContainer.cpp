#include "stdafx.h"
#include "GlobalDefines.h"
#include "Singleton.h"
#include "GlobalDefines.h"
#include "BaseStream.h"
#include "BinaryReader.h"
#include "Record.h"
#include "RecordFactory.h"
#include "RegularContainer.h"
#include "SlidePersistAtom.h"
#include "GrColorAtom.h"
#include "TabStop.h"
#include "CharacterRun.h"
#include "ParagraphRun.h"
#include "OutlineTextRefAtom.h"
#include "TextHeaderAtom.h"
#include "SlideListWithText.h"
#include "List.h"
#include "DocumentContainer.h"
#include <algorithm>


DocumentContainer::DocumentContainer()
{
}

DocumentContainer::DocumentContainer(shared_ptr<BinaryReader> spBinaryReader,
	unsigned long size,
	unsigned long typeCode,
	unsigned int version,
	unsigned int instance)
	: RegularContainer(spBinaryReader, size, typeCode, version, instance)
{
	vector<shared_ptr<SlideListWithText>> vec = this->AllChildrenWithType<SlideListWithText>();
	for (auto& ele : vec)
	{
		auto innerFunc = [](vector<shared_ptr<SlidePersistAtom>>& target, shared_ptr <SlideListWithText > sp){
			for (auto& atom : sp->AllChildrenWithType<SlidePersistAtom>())
			{
				target.push_back(atom);
			}
		};

		switch ((SlideListWidthTextSpace::TextInstance)ele->Instance)
		{
		case SlideListWidthTextSpace::CollectionOfMasterSlides:
			innerFunc(this->MasterPersistList, ele);
			break;
		case SlideListWidthTextSpace::CollectionOfNotesSlides:
			innerFunc(this->NotesPersistList, ele);
			break;
		case SlideListWidthTextSpace::CollectionOfSlides:
			innerFunc(this->SlidePersistList, ele);
			break;
		default:
			break;
		}
	}

	//定义升序比较lambda函数
	auto LessSort = [](shared_ptr<SlidePersistAtom> a, shared_ptr<SlidePersistAtom> b){return a->PersistIdRef < b->PersistIdRef; };

	std::sort(MasterPersistList.begin(), MasterPersistList.end(), LessSort);
	std::sort(NotesPersistList.begin(), NotesPersistList.end(), LessSort);
	std::sort(SlidePersistList.begin(), SlidePersistList.end(), LessSort);

	this->_spDocInfoListContainer = FirstChildWithType<List>();
}


DocumentContainer::~DocumentContainer()
{
}

std::shared_ptr<SlidePersistAtom> DocumentContainer::SlidePersistAtomForSlideWithIdx(unsigned long idx)
{
	for (auto& ele : this->SlidePersistList)
	{
		// idx is zero-based, psr-reference is one-based
		if (ele->PersistIdRef == idx + 1)
			return ele;
	}

	return nullptr;
}
