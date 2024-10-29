#include "pch.h"
#include "CScene_Result.h"

#include "CCore.h"
#include "CKeyMgr.h"
#include "CGameMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CSound.h"
#include "CResMgr.h"

#include "CTextUI.h"
#include "CBtnUI.h"
#include "CObject.h"

CScene_Result::CScene_Result()
	: m_bMoveSceneLock(false)
{
}

CScene_Result::~CScene_Result()
{
}

void CScene_Result::GoToTitleScene()
{
	if (m_bMoveSceneLock)
	{
		CSoundMgr::GetInst()->Play_SFX(L"UI_Click_Error");
		return;
	}

	m_bMoveSceneLock = true;

	ChangeScene(SCENE_TYPE::TITLE);
}

void CScene_Result::Update()
{
	CScene::Update();
}
void CScene_Result::Enter()
{
	CGameMgr::GetInst()->SaveGameInfo();

	m_bMoveSceneLock = false;
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	CTextUI* textUI = new CTextUI(L"Result", 60);
	textUI->SetPos(Vector2(vResolution.x / 2.f, 200.f));
	AddObject(textUI, GROUP_TYPE::UI_OBJECT);
	
	wstring str = L"최고 점수 : ";
	str += std::to_wstring(CGameMgr::GetInst()->GetMaxScore());
	CTextUI* maxScoreTextUI = new CTextUI(str, 40);
	maxScoreTextUI->SetPos(Vector2(vResolution.x / 2.f, 400.f));
	AddObject(maxScoreTextUI, GROUP_TYPE::UI_OBJECT);

	str = L"현재 점수 : ";
	str += std::to_wstring(CGameMgr::GetInst()->GetGameInfo().score);
	CTextUI* currScoreTextUI = new CTextUI(str , 40);
	currScoreTextUI->SetPos(Vector2(vResolution.x / 2.f, 500.f));
	AddObject(currScoreTextUI, GROUP_TYPE::UI_OBJECT);

	CBtnUI* pGoToTitleBtnUI = new CBtnUI(L"타이틀로", 20);
	pGoToTitleBtnUI->SetName(L"GoToTitleBtn");
	pGoToTitleBtnUI->SetScale(Vector2(200.f, 50.f));
	pGoToTitleBtnUI->SetPos(Vector2((vResolution.x / 2.f) - (pGoToTitleBtnUI->GetScale().x / 2.f)
		, (vResolution.y / 2.f) - (pGoToTitleBtnUI->GetScale().y / 2.f) + 200.f));
	pGoToTitleBtnUI->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Result::GoToTitleScene);
	AddObject(pGoToTitleBtnUI, GROUP_TYPE::UI);

	CSoundMgr::GetInst()->Play_BGM(L"ResultBgm");
}

void CScene_Result::Exit()
{
	DeleteAll();
}
