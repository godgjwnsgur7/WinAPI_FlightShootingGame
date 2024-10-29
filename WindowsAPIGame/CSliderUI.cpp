#include "pch.h"
#include "CSliderUI.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CSliderHandleUI.h"
#include "SelectGDI.h"

CSliderUI::CSliderUI(Vector2 _vScale, Vector2 _vPos)
	: CUI(false)
	, m_bMouseClickState(false)
	, m_pSettingPopupFunc(nullptr)
	, m_pSettingPopupInst(nullptr)
	, m_fSliderValue(0.f)
{
	m_vScale = _vScale;
	m_vPos = _vPos;

	m_pHandleUI = new CSliderHandleUI;
	m_pHandleUI->SetScale(Vector2(m_vScale.y * 2.f, m_vScale.y * 2.f));
	m_pHandleUI->SetPos(Vector2((m_vScale.x / 2.f) - (m_pHandleUI->GetScale().x / 2.f)
		, (m_vScale.y / 2.f) - (m_pHandleUI->GetScale().y / 2.f)));
	((CSliderHandleUI*)m_pHandleUI)->SetClickedCallBack(this, (SLIDER_MEMFUNC)&CSliderUI::OnChangedValue);
	AddChild(m_pHandleUI);
}

CSliderUI::~CSliderUI()
{
}

void CSliderUI::OnChangedValue()
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	float posX = MOUSE_POS.x - (m_pParentUI->GetPos().x - (m_vScale.x / 2.f)) - (m_pParentUI->GetScale().x / 2.f);

	float minPosX = m_vPos.x - (m_vScale.x / 2.f) - (m_pHandleUI->m_vScale.x / 2.f);
	float maxPosX = m_vPos.x + (m_vScale.x / 2.f) - (m_pHandleUI->m_vScale.x / 2.f);

	if (posX < minPosX) posX = minPosX;
	if (posX > maxPosX) posX = maxPosX;

	m_pHandleUI->SetPos(Vector2(posX, m_pHandleUI->GetPos().y));

	// 0.f ~ 100.f
	float sliderValue = posX / m_vScale.x * 100.f;
	sliderValue += 5;
	m_fSliderValue = sliderValue;

	if (m_pSettingPopupInst && m_pSettingPopupFunc)
	{
		((*m_pSettingPopupInst).*m_pSettingPopupFunc)(sliderValue);
	}
}

void CSliderUI::SetSliderValue(float _f)
{
	m_fSliderValue = _f;
	float posX = m_vPos.x - (m_vScale.x / 2.f) - (m_pHandleUI->m_vScale.x / 2.f);
	m_pHandleUI->SetPos(Vector2(posX + _f * 2.f, m_pHandleUI->GetPos().y));

	if (m_pSettingPopupInst && m_pSettingPopupFunc)
	{
		((*m_pSettingPopupInst).*m_pSettingPopupFunc)(_f);
	}
}

void CSliderUI::Update()
{
	CUI::Update();
}

void CSliderUI::Render(HDC _dc)
{
	Vector2 vPos = GetFinalPos();
	Vector2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	SelectGDI select1(_dc, PEN_TYPE::WHITE);
	SelectGDI select2(_dc, BRUSH_TYPE::BLACK);
	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	SelectGDI select3(_dc, PEN_TYPE::HOLLOW);
	SelectGDI select4(_dc, BRUSH_TYPE::RED);
	Rectangle(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x * (m_fSliderValue / 100))
		, (int)(vPos.y + vScale.y));

	Render_Child(_dc);
}

void CSliderUI::MouseOn()
{
}

void CSliderUI::MouseLbtnDown()
{
	m_bMouseClickState = true;
}

void CSliderUI::MouseLbtnUp()
{
}

void CSliderUI::MouseLbtnClicked()
{
}
