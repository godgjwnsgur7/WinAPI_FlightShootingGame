#include "pch.h"
#include "CSettingPopupUI.h"

#include "CTextUI.h"
#include "CSliderUI.h"
#include "CSoundMgr.h"

CSettingPopupUI::CSettingPopupUI()
{
	CSoundMgr::GetInst()->LoadSoundInfo();

	m_pTitleTextUI = new CTextUI(L"Setting Popup", 30);

	m_pBgmTextUI = new CTextUI(L"BGM", 20);
	m_pSfxTextUI = new CTextUI(L"SFX", 20);

	m_pBgmValueTextUI = new CTextUI(std::to_wstring(CSoundMgr::GetInst()->GetBGMVolume()), 20);
	m_pSfxValueTextUI = new CTextUI(std::to_wstring(CSoundMgr::GetInst()->GetSFXVolume()), 20);
}

CSettingPopupUI::~CSettingPopupUI()
{
	if (nullptr != m_pTitleTextUI)
		delete m_pTitleTextUI;
	if (nullptr != m_pBgmTextUI)
		delete m_pBgmTextUI;
	if (nullptr != m_pBgmValueTextUI)
		delete m_pBgmValueTextUI;
	if (nullptr != m_pSfxTextUI)
		delete m_pSfxTextUI;
	if (nullptr != m_pSfxValueTextUI)
		delete m_pSfxValueTextUI;
}

void CSettingPopupUI::OnChangedBgmVolume(float _f)
{
	CSoundMgr::GetInst()->SetBGMVolume(_f);
	m_pBgmValueTextUI->SetTextStr(std::to_wstring((int)_f));
}

void CSettingPopupUI::OnChangedSfxVolume(float _f)
{
	CSoundMgr::GetInst()->SetSFXVolume(_f);
	m_pSfxValueTextUI->SetTextStr(std::to_wstring((int)_f));
}

void CSettingPopupUI::Update()
{
	CPopupUI::Update();

	m_pTitleTextUI->SetPos(GetPos() + Vector2(GetScale().x / 2.f, GetScale().y / 7.f));

	m_pBgmTextUI->SetPos(GetPos() + Vector2(GetScale().x / 6.f, GetScale().y / 2.6f));
	m_pSfxTextUI->SetPos(GetPos() + Vector2(GetScale().x / 6.f, GetScale().y / 1.8f));

	m_pBgmValueTextUI->SetPos(GetPos() + Vector2(GetScale().x - 70.f, GetScale().y / 2.6f));
	m_pSfxValueTextUI->SetPos(GetPos() + Vector2(GetScale().x - 70.f, GetScale().y / 1.8f));
}

void CSettingPopupUI::FinalUpdate()
{
	CUI::FinalUpdate();
}

void CSettingPopupUI::Render(HDC _dc)
{
	CPopupUI::Render(_dc);

	m_pTitleTextUI->Render(_dc);
	m_pBgmTextUI->Render(_dc);
	m_pBgmValueTextUI->Render(_dc);
	m_pSfxTextUI->Render(_dc);
	m_pSfxValueTextUI->Render(_dc);
}

void CSettingPopupUI::MouseOn()
{
	CPopupUI::MouseOn();
}

void CSettingPopupUI::MouseLbtnDown()
{
	CPopupUI::MouseLbtnDown();
}

void CSettingPopupUI::MouseLbtnUp()
{
	CPopupUI::MouseLbtnUp();
}
