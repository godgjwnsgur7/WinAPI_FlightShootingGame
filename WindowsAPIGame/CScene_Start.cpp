#include "pch.h"
#include "CScene_Start.h"
#include "CGameMgr.h"
#include "CCore.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CPlayerSubUnit.h"
#include "CMonster.h"
#include "CBossMonster.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CItem.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

#include "CBackgroundGroup.h"

#include "CWall.h"
#include "CWallGroup.h"

#include "CPlayerInfoUI.h"
#include "CScoreTextUI.h"

#include "CResMgr.h"
#include "CSound.h"

CScene_Start::CScene_Start()
	: m_fForceRadius(500.f)
	, m_fCurrRadius(0.f)
	, m_fForce(0.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (vecObj[j]->GetRigidBody())
				{
					Vector2 vDiff = m_vForcePos - vecObj[j]->GetPos();
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce =	m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}

				vecObj[j]->Update();
			}
		}
	}

	/* 카메라 디버그용
	if (KEY_TAP(KEY::LBTN))
	{
		Vector2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
	*/

	CGameMgr::GetInst()->Update();
}

void CScene_Start::Render(HDC _dc)
{
	CScene::Render(_dc);

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurrRadius += m_fForceRadius * 2.f * fDT;
	if (m_fCurrRadius > m_fForceRadius)
	{
		m_fCurrRadius = 0.f;
	}
}

void CScene_Start::Enter()
{
	CGameMgr::GetInst()->LoadGameInfo();
	CSoundMgr::GetInst()->Play_BGM(L"InGameBgm");
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	// Background
	CObject* pBackground = new CBackgroundGroup;
	pBackground->SetName(L"Background");
	pBackground->SetScale(Vector2(535.f, 1130.f));
	pBackground->SetPos(Vector2(vResolution.x / 2.f, vResolution.y / 2.f));
	AddObject(pBackground, GROUP_TYPE::GROUND);

	// Wall
	CWallGroup* pWall = new CWallGroup;

	// Player
	CObject* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(Vector2(535.f / 2.f, 800.f));
	pPlayer->SetScale(Vector2(100.f, 100.f));
	AddObject(pPlayer, GROUP_TYPE::PLAYER);
	RegisterPlayer(pPlayer);
	CGameMgr::GetInst()->SetPlayer((CPlayer*)pPlayer);

	// UI
	CPlayerInfoUI* pPlayerInfoUI = new CPlayerInfoUI;
	AddObject(pPlayerInfoUI, GROUP_TYPE::UI);

	// 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::PROJ_MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_MONSTER, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::WALL);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::ITEM, GROUP_TYPE::PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOSSMONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::BOSSMONSTER, GROUP_TYPE::PLAYER);

	// 카메라 타겟 지정
	CCamera::GetInst()->SetCurrLookAt(vResolution / 2.f);

	Start();
	CGameMgr::GetInst()->StartGame();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
