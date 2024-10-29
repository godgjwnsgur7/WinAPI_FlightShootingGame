#include "pch.h"
#include "CUI.h"

#include "CObject.h"
#include "CKeyMgr.h"
#include "CCamera.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	: m_vecChildUI{}
	, m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	, m_vecChildUI{}
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	SafeDeleteVector(m_vecChildUI);
}

void CUI::AddChild(CUI* _pUI)
{
	m_vecChildUI.push_back(_pUI);
	_pUI->m_pParentUI = this;
}

void CUI::Update()
{
	Update_Child();
}

void CUI::FinalUpdate()
{
	CObject::FinalUpdate();

	m_vFinalPos = GetPos();

	if (GetParent())
	{
		Vector2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}

	MouseOnCheck();

	FinalUpdate_Child();
}

void CUI::Render(HDC _dc)
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

		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	else
	{
		SelectGDI select(_dc, BRUSH_TYPE::BLACK);

		Rectangle(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}

	Render_Child(_dc);
}

void CUI::SetDead()
{
	CObject::SetDead();

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->SetDead();
	}
}

void CUI::Update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void CUI::FinalUpdate_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->FinalUpdate();
	}
}

void CUI::Render_Child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vector2 vMousePos = MOUSE_POS;
	Vector2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}

	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}


void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{

}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}