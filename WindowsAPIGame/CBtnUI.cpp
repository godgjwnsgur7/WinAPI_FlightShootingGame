#include "pch.h"
#include "CBtnUI.h"

#include "CTextUI.h"

CBtnUI::CBtnUI()
	: CUI(false)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
	, m_pTextUI(nullptr)
{
}

CBtnUI::CBtnUI(wstring _textStr, int _iTextSize)
	: CUI(false)
	, m_pSceneInst(nullptr)
	, m_pSceneFunc(nullptr)
{
	m_pTextUI = new CTextUI(_textStr, _iTextSize);
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::Update()
{
	CUI::Update();

	if (m_pTextUI != nullptr)
		m_pTextUI->SetPos(GetFinalPos() + Vector2((GetScale().x / 2.f), (GetScale().y / 4.f)));
}

void CBtnUI::Render(HDC _dc)
{
	CUI::Render(_dc);

	if (m_pTextUI != nullptr)
		m_pTextUI->Render(_dc);
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}

void CBtnUI::MouseLbtnClicked()
{
	if (m_pSceneInst && m_pSceneFunc)
	{
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}