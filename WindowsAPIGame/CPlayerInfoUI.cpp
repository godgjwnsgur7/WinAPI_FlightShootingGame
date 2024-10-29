#include "pch.h"
#include "CPlayerInfoUI.h"

#include "CCore.h"
#include "CGameMgr.h"
#include "CPathMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CTexture.h"
#include "CScoreTextUI.h"

CPlayerInfoUI::CPlayerInfoUI()
	: CUI(false)
	, m_pLifeTex{}
	, m_pBoomTex{}
	, m_iMaxCount(3)
	, m_iCurrLifeCount(3)
	, m_iCurrBoomCount(3)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	m_pLifeTex = new CTexture;
	m_pLifeTex->Load(strFilePath + L"texture\\LifeIcon.bmp");
	m_pBoomTex = new CTexture;
	m_pBoomTex->Load(strFilePath + L"texture\\BoomIcon.bmp");

	m_vPos = Vector2(0.f, 0.f);	

	m_pScoreTextUI = new CScoreTextUI;
	m_pScoreTextUI->SetPos(Vector2(vResolution.x / 2.f, 10.f));
	CSceneMgr::GetInst()->GetCurrScene()->AddObject(m_pScoreTextUI, GROUP_TYPE::UI);
}

CPlayerInfoUI::~CPlayerInfoUI()
{
}

void CPlayerInfoUI::Update()
{
	const tGameInfo gameInfo = CGameMgr::GetInst()->GetGameInfo();
	m_iCurrLifeCount = gameInfo.life;
	m_iCurrBoomCount = gameInfo.boomCount;
	m_pScoreTextUI->SetScore(gameInfo.score);
}

void CPlayerInfoUI::Render(HDC _dc)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	int size = 40;

	// Life
	for (int i = 0; i < m_iCurrLifeCount; i++)
	{
		TransparentBlt(_dc
			, size * i, 0, size, size
			, m_pLifeTex->GetDC()
			, 0, 0
			, 18, 18
			, RGB(255, 0, 255)
		);
	}
	
	// Boom
	for (int i = 1; i <= m_iCurrBoomCount; i++)
	{ 
		TransparentBlt(_dc
			, vResolution.x - (size * i), 0, size, size
			, m_pBoomTex->GetDC()
			, 0, 0
			, 18, 18
			, RGB(255, 0, 255)
		);
	}
}
