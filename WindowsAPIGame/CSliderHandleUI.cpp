#include "pch.h"
#include "CSliderHandleUI.h"

#include "SelectGDI.h"
#include "CKeyMgr.h"

CSliderHandleUI::CSliderHandleUI()
{
}

CSliderHandleUI::~CSliderHandleUI()
{
}

void CSliderHandleUI::Update()
{
	if (m_bLbtnDown)
	{
		if (m_pSliderInst && m_pSliderFunc)
		{
			((*m_pSliderInst).*m_pSliderFunc)();
		}
	}
}

void CSliderHandleUI::Render(HDC _dc)
{
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	SelectGDI select(_dc, PEN_TYPE::WHITE);
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, BRUSH_TYPE::GRAY);

		Ellipse(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y)
		);
	}
	else
	{
		SelectGDI select(_dc, BRUSH_TYPE::BLACK);

		Ellipse(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y)
		);
	}

	Render_Child(_dc);
}

void CSliderHandleUI::MouseOn()
{
}

void CSliderHandleUI::MouseLbtnDown()
{

}

void CSliderHandleUI::MouseLbtnUp()
{
}

void CSliderHandleUI::MouseLbtnClicked()
{
	
}
