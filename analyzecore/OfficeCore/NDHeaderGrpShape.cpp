#include "stdafx.h"
#include "NDShapeProperties.h"
#include "NDShape.h"
#include "NDHeaderGrpShape.h"


CNDHeaderGrpShape::CNDHeaderGrpShape(shared_ptr<ShapeContainer>& spShapeContainer)
	: CNDShape(spShapeContainer)
{
}


CNDHeaderGrpShape::~CNDHeaderGrpShape()
{
}

NDShapeType CNDHeaderGrpShape::GetShapeType()
{
	return NDShapeType::HeaderGroupShape;
}

std::shared_ptr<NDNVGrpShapeProperties> CNDHeaderGrpShape::GetNvGrpSpPr()
{
	if (m_spShapeContainer == nullptr
		|| m_spNvGrpSpPr != nullptr)
		return m_spNvGrpSpPr;

	// ��ʼ��
	shared_ptr<GroupShapeRecord> spGroupShapeRecord = m_spShapeContainer->FirstChildWithType<GroupShapeRecord>();
	if (spGroupShapeRecord == nullptr)
		return m_spNvGrpSpPr;

	m_spNvGrpSpPr = make_shared<NDNVGrpShapeProperties>();
	m_spNvGrpSpPr->spCNvPr = make_shared<NDNVCanvasProperties>();
	m_spNvGrpSpPr->spCNvPr->spId = m_spShapeContainer->Index;
	m_spNvGrpSpPr->spCNvPr->strName = _T("");	//TODO:

	m_spGrpSpPr = make_shared<NDGrpShapeProperties>();
	m_spGrpSpPr->spXfrm = make_shared<NDXfrm>();
	m_spGrpSpPr->spXfrm->ptOff = Point(0, 0);
	m_spGrpSpPr->spXfrm->sizeExt = Size(0, 0);
	m_spGrpSpPr->spXfrm->ptChOff = Point(0, 0);
	m_spGrpSpPr->spXfrm->sizeChExt = Size(0, 0);
}
