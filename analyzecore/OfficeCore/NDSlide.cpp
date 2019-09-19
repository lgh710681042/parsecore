#include "stdafx.h"
#include "NDShape.h"
#include "NDGroupContainer.h"
#include "NDDrawingContainer.h"
#include "NDPPDrawing.h"
#include "NDSlide.h"



CNDSlide::CNDSlide(shared_ptr<Slide>& spSlide)
	: m_spSlide(spSlide)
{

}

CNDSlide::~CNDSlide()
{
}

std::vector<std::shared_ptr<CNDShape>> CNDSlide::GetShapes()
{
	vector<std::shared_ptr<CNDShape>> vecNDShapes;

	if (m_spSlide == nullptr 
		|| m_spNDPPDrawing != nullptr)
		return vecNDShapes;

	// 1.��ȡPPDrawing
	shared_ptr<PPDrawing> spPPDrawing = m_spSlide->FirstChildWithType<PPDrawing>();
	if (spPPDrawing == nullptr)
		return vecNDShapes;

	m_spNDPPDrawing = make_shared<CNDPPDrawing>(spPPDrawing);
	if (m_spNDPPDrawing == nullptr)
		return vecNDShapes;

	// 2.��ȡDrawingContainer����
	vector<shared_ptr<CNDDrawingContainer>> vecNDDrawingContainers = m_spNDPPDrawing->GetDrawingConatiners();
	for (auto& drawingContainer : vecNDDrawingContainers)
	{
		// 3.��ȡGroupContainer
		shared_ptr<CNDGroupContainer> spNDGroupContainer = drawingContainer->GetGroupContainer();
		if (spNDGroupContainer == nullptr)
			continue;

		//TODO: �Ż��ռ�
		vector<std::shared_ptr<CNDShape>> vecTmp = spNDGroupContainer->GetNDShapes();
		for (auto& ele : vecTmp)
		{
			vecNDShapes.push_back(ele);
		}
	}

	return vecNDShapes;
}
