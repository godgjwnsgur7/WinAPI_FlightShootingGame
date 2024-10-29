#include "pch.h"
#include "CScene_Title.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CSceneMgr.h"

#include "CObject.h"
#include "CTextUI.h"
#include "CBtnUI.h"

#include "CResMgr.h"
#include "CSound.h"

#include "CUI.h"
#include "CUIMgr.h"
#include "CPopupUI.h"
#include "CBtnUI.h"
#include "CSettingPopupUI.h"
#include "CSliderUI.h"

extern HWND g_hWnd;

CScene_Title::CScene_Title()
	: m_pSettingPopupUI(nullptr)
	, m_bGameStartLock(false)
{
}

CScene_Title::~CScene_Title()
{
}

void CScene_Title::GoToGameScene()
{
	if (m_bGameStartLock || m_pSettingPopupUI != nullptr)
	{
		CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Error");
		return;
	}

	m_bGameStartLock = true;

	ChangeScene(SCENE_TYPE::START);
	CSoundMgr::GetInst()->Play_SFX(L"UI_GameStartInfo");
}

void CScene_Title::ExitGame()
{
	if (m_bGameStartLock || m_pSettingPopupUI != nullptr)
	{
		CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Error");
		return;
	}

	DestroyWindow(g_hWnd);
}

void CScene_Title::OpenSettingPopupUI()
{
	if (m_bGameStartLock || m_pSettingPopupUI != nullptr)
	{
		CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Error");
		return;
	}

	CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Enter");
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	m_pSettingPopupUI = new CSettingPopupUI;
	m_pSettingPopupUI->SetName(L"SettingPopupUI");
	m_pSettingPopupUI->SetScale(Vector2(400.f, 400.f));
	m_pSettingPopupUI->SetPos(Vector2((vResolution.x / 2.f) - (m_pSettingPopupUI->GetScale().x / 2.f)
		, (vResolution.y / 2.f) - (m_pSettingPopupUI->GetScale().y / 2.f)));

	CBtnUI* pCloseBtnUI = new CBtnUI(L"Close", 20);
	pCloseBtnUI->SetName(L"CloseUI");
	pCloseBtnUI->SetScale(Vector2(100.f, 40.f));
	pCloseBtnUI->SetPos(Vector2((m_pSettingPopupUI->GetScale().x / 2.f) - (pCloseBtnUI->GetScale().x / 2.f)
		, m_pSettingPopupUI->GetScale().y - (pCloseBtnUI->GetScale().y) - 50.f));
	((CBtnUI*)pCloseBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Title::CloseSettingPopupUI);
	m_pSettingPopupUI->AddChild(pCloseBtnUI);

	CSliderUI* pBgmSliderUI = new CSliderUI(Vector2(200.f, 10.f)
		, Vector2((m_pSettingPopupUI->GetScale().x / 2.f) - (200.f / 2.f)
			, (m_pSettingPopupUI->GetScale().y / 2.5f)));
	pBgmSliderUI->SetName(L"BgmSliderUI");
	pBgmSliderUI->SetSliderValue(CSoundMgr::GetInst()->GetBGMVolume());
	pBgmSliderUI->SetValueChangedCallBack(m_pSettingPopupUI, (SETTINGPOPUP_MEMFUNC)&CSettingPopupUI::OnChangedBgmVolume);
	m_pSettingPopupUI->AddChild(pBgmSliderUI);

	CSliderUI* pSfxSliderUI = new CSliderUI(Vector2(200.f, 10.f)
		, Vector2((m_pSettingPopupUI->GetScale().x / 2.f) - (200.f / 2.f)
			, (m_pSettingPopupUI->GetScale().y / 1.75f)));
	pSfxSliderUI->SetName(L"SfxSliderUI");
	pSfxSliderUI->SetSliderValue(CSoundMgr::GetInst()->GetSFXVolume());
	pSfxSliderUI->SetValueChangedCallBack(m_pSettingPopupUI, (SETTINGPOPUP_MEMFUNC)&CSettingPopupUI::OnChangedSfxVolume);
	m_pSettingPopupUI->AddChild(pSfxSliderUI);

	AddObject(m_pSettingPopupUI, GROUP_TYPE::UI);
}

void CScene_Title::CloseSettingPopupUI()
{
 	CUIMgr::GetInst()->SetFocusedUI(nullptr);
	if (m_pSettingPopupUI != nullptr)
	{
		CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Cancel");
		DeleteObject(m_pSettingPopupUI);
		m_pSettingPopupUI = nullptr;
	}
}

void CScene_Title::Update()
{
	CScene::Update();
}

void CScene_Title::Enter() 
{
	m_bGameStartLock = false;
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	CTextUI* textUI = new CTextUI(L"Jun's Shooting", 60);
	textUI->SetPos(Vector2(vResolution.x / 2.f, 200.f));
	AddObject(textUI, GROUP_TYPE::UI_OBJECT);

	CBtnUI* pStartBtnUI = new CBtnUI(L"게임 시작", 20);
	pStartBtnUI->SetName(L"StartBtnUI");
	pStartBtnUI->SetScale(Vector2(200.f, 50.f));
	pStartBtnUI->SetPos(Vector2((vResolution.x / 2.f) -(pStartBtnUI->GetScale().x / 2.f)
		, (vResolution.y / 2.f) - (pStartBtnUI->GetScale().y / 2.f)));
	((CBtnUI*)pStartBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Title::GoToGameScene);
	AddObject(pStartBtnUI, GROUP_TYPE::UI);
	
	CBtnUI* pSettingUI = new CBtnUI(L"설정", 20);
	pSettingUI->SetName(L"StartBtnUI");
	pSettingUI->SetScale(Vector2(200.f, 50.f));
	pSettingUI->SetPos(Vector2((vResolution.x / 2.f) - (pSettingUI->GetScale().x / 2.f)
		, (vResolution.y / 2.f) - (pSettingUI->GetScale().y / 2.f) + 100.f));
	((CBtnUI*)pSettingUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Title::OpenSettingPopupUI);
	AddObject(pSettingUI, GROUP_TYPE::UI);

	CBtnUI* pExitGameBtnUI = new CBtnUI(L"게임 종료", 20);
	pExitGameBtnUI->SetName(L"StartBtnUI");
	pExitGameBtnUI->SetScale(Vector2(200.f, 50.f));
	pExitGameBtnUI->SetPos(Vector2((vResolution.x / 2.f) - (pExitGameBtnUI->GetScale().x / 2.f)
		, (vResolution.y / 2.f) - (pExitGameBtnUI->GetScale().y / 2.f) + 200.f));
	((CBtnUI*)pExitGameBtnUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Title::ExitGame);
	AddObject(pExitGameBtnUI, GROUP_TYPE::UI);

	CSoundMgr::GetInst()->Play_BGM(L"TitleBgm");
}

void CScene_Title::Exit()
{
	DeleteAll();
}
