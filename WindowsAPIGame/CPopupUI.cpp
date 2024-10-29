#include "CPopupUI.h"

#include "CKeyMgr.h"

CPopupUI::CPopupUI()
	: CUI(false)
{

}

CPopupUI::~CPopupUI()
{

}

void CPopupUI::Update()
{
	CUI::Update();
}

void CPopupUI::Render(HDC _dc)
{
	CUI::Render(_dc);
}

void CPopupUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vector2 vDiff = MOUSE_POS - vDragStart;

		Vector2 vCurrPos = GetPos();
		vCurrPos += vDiff;
		SetPos(vCurrPos);

		vDragStart = MOUSE_POS;
	}
}

void CPopupUI::MouseLbtnDown()
{
	vDragStart = MOUSE_POS;
}

void CPopupUI::MouseLbtnUp()
{

}