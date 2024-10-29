#include "pch.h"
#include "CPlayer.h"
#include "CPlayerSubUnit.h"

#include "CCore.h"
#include "CGameMgr.h"
#include "CPathMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CItem.h"
#include "CMissile.h"
#include "CExplosion.h"
#include "CBoomEffect.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

#include "CRigidBody.h"
#include "CSound.h"

CPlayer::CPlayer()
	: m_eCurrState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::MOVE)
	, m_pBoomEffect(nullptr)
	, m_iDir(1)
	, m_iPrevDir(1)
	, m_iPower(1)
	, m_fSpeed(250.f)
	, m_fAttackDelay(0.25f)
	, m_fCurrAttackDelay(0.f)
	, m_fTimer(0.f)
	, m_bInvincibleState(false)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2(0.f, 0.f));
	GetCollider()->SetScale(Vector2(25.f, 25.f));

	CreateRigidBody();

	CTexture* pPlayerTex = CResMgr::GetInst()->LoadTexture(L"Player", L"texture\\Player.bmp");
	
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE", pPlayerTex, Vector2(0.f, 0.f), Vector2(48.f, 48.f), Vector2(50.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"MOVE_LEFT", pPlayerTex, Vector2(0.f, 100.f), Vector2(48.f, 48.f), Vector2(50.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"MOVE_RIGHT", pPlayerTex, Vector2(0.f, 50.f), Vector2(48.f, 48.f), Vector2(50.f, 0.f), 0.1f, 4);
	GetAnimator()->CreateAnimation(L"DEAD", pPlayerTex, Vector2(0.f, 0.f), Vector2(0.f, 0.f), Vector2(0.f, 0.f), 0.1f, 1);
}
 
CPlayer::~CPlayer()
{

}

void CPlayer::OnDestoryBoomEffect()
{
	if (m_pBoomEffect != nullptr)
	{
		DeleteObject(m_pBoomEffect);
		m_pBoomEffect = nullptr;
	}
}

void CPlayer::Update()
{
	if (m_eCurrState == PLAYER_STATE::DEAD)
	{
		if (CGameMgr::GetInst()->IsGameOver())
			return;

		UpdateAnimation();
		m_ePrevState = m_eCurrState;

		m_fTimer += fDT;
		
		// 파괴 후 재생성 시간
		if (m_fTimer >= 1.5f)
		{
			SetPos(Vector2(535.f / 2.f, 800.f));
			m_eCurrState = PLAYER_STATE::IDLE;
			m_bInvincibleState = true;
			m_fTimer = 0.f;
		}
		return;
	}

	if (m_bInvincibleState)
	{
		m_fTimer += fDT;

		// 무적 시간
		if (m_fTimer >= 1.f)
		{
			m_bInvincibleState = false;
			m_fTimer = 0.f;
		}
	}

	UpdateMove();
	UpdateState();
	UpdateAnimation();
	GetAnimator()->Update();

	m_ePrevState = m_eCurrState;
	m_iPrevDir = m_iDir;
}

void CPlayer::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CPlayer::CreateMissile()
{
	Vector2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 3.f;

	CSoundMgr::GetInst()->Play_SFX(L"Shoot", 50.f);

	switch (m_iPower)
	{
	case 1:
	{
		CMissile* pMissile1 = new CMissile(MISSILE_TYPE::PLAYER_1
			, vMissilePos, Vector2(0.f, -1.f));
		pMissile1->SetName(L"Missile_Player");
		CreateObject(pMissile1, GROUP_TYPE::PROJ_PLAYER);
	}
		break;
	case 2:
	{
		CMissile* pMissile1 = new CMissile(MISSILE_TYPE::PLAYER_1
			, vMissilePos + Vector2(-7.f, 0.f), Vector2(0.f, -1.f));
		pMissile1->SetName(L"Missile_Player");
		CMissile* pMissile2 = new CMissile(MISSILE_TYPE::PLAYER_1
			, vMissilePos + Vector2(7.f, 0.f), Vector2(0.f, -1.f));
		pMissile2->SetName(L"Missile_Player");

		CreateObject(pMissile1, GROUP_TYPE::PROJ_PLAYER);
		CreateObject(pMissile2, GROUP_TYPE::PROJ_PLAYER);
	}
		break;
	case 3:
	{
		CMissile* pMissile1 = new CMissile(MISSILE_TYPE::PLAYER_2
			, vMissilePos, Vector2(0.f, -1.f));
		pMissile1->SetName(L"Missile_Player");

		CreateObject(pMissile1, GROUP_TYPE::PROJ_PLAYER);
	}
	break;
	default: // 4이상
	{
		CMissile* pMissile1 = new CMissile(MISSILE_TYPE::PLAYER_1
			, vMissilePos + Vector2(17.5f, 7.5f), Vector2(0.f, -1.f));
		pMissile1->SetName(L"Missile_Player");
		CreateObject(pMissile1, GROUP_TYPE::PROJ_PLAYER);

		CMissile* pMissile2 = new CMissile(MISSILE_TYPE::PLAYER_2
			, vMissilePos, Vector2(0.f, -1.f));
		pMissile2->SetName(L"Missile_Player");
		CreateObject(pMissile2, GROUP_TYPE::PROJ_PLAYER);
		
		CMissile* pMissile3 = new CMissile(MISSILE_TYPE::PLAYER_1
			, vMissilePos + Vector2(-17.5f, 7.5f), Vector2(0.f, -1.f));
		pMissile3->SetName(L"Missile_Player");
		CreateObject(pMissile3, GROUP_TYPE::PROJ_PLAYER);
	}
		break;
	}
}

void CPlayer::DestroyMine()
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	m_eCurrState = PLAYER_STATE::DEAD;
	DestroyAllSubUnit();

	CExplosion* explosion = new CExplosion;
	explosion->SetPos(GetPos());
	explosion->SetAnimScaleSize(3.f);
	CreateObject(explosion, GROUP_TYPE::EXPLOSION_EFFECT);
	CSoundMgr::GetInst()->Play_SFX(L"Death");
	m_iPower = 1;

	CObject* pItem = new CItem(ITEM_TYPE::POWER, Vector2(m_vPos));
	pItem->SetName(L"PowerItem");
	CSceneMgr::GetInst()->GetCurrScene()->AddObject(pItem, GROUP_TYPE::ITEM);

	if (CGameMgr::GetInst()->IsUseLife())
	{
		SetPos(Vector2(vResolution.x / 2.f, vResolution.y * 2.f));
	}
	else
	{
		DeleteObject(this);
	}
}

void CPlayer::UpdateState()
{
	m_iDir = 0;

	if (KEY_HOLD(KEY::A))
	{
		m_iDir--;
		m_eCurrState = PLAYER_STATE::MOVE;
	}
	if (KEY_HOLD(KEY::D))
	{
		m_iDir++;
		m_eCurrState = PLAYER_STATE::MOVE;
	}
	if (m_iDir == 0.f)
	{
		m_eCurrState = PLAYER_STATE::IDLE;
	}

	if (KEY_HOLD(KEY::SPACE))
	{
		m_fCurrAttackDelay += fDT;

		if (m_fCurrAttackDelay > m_fAttackDelay)
		{
			m_fCurrAttackDelay -= m_fAttackDelay;
			CreateMissile();
		}
	}

	if (KEY_TAP(KEY::Q))
	{
		m_iPower++;

		if (4 < m_iPower && m_iPower < 8)
			SummonSubUnit();
	}
	if (KEY_TAP(KEY::E))
	{
		m_iPower = 1;
		DestroyAllSubUnit();
	}
	if (m_pBoomEffect == nullptr && KEY_TAP(KEY::R) && CGameMgr::GetInst()->IsUseBoom())
	{
		CSoundMgr::GetInst()->Play_SFX(L"Boom", 50.f);

		Vector2 vResolution = CCore::GetInst()->GetResolution();

		m_pBoomEffect = new CBoomEffect();
		m_pBoomEffect->SetName(L"BoomEffect");
		m_pBoomEffect->SetPos(Vector2(vResolution / 2.f));
		m_pBoomEffect->SetAnimScaleSize(7.f);
		m_pBoomEffect->SetDestroyCallBack(this, (PLAYER_MEMFUNC)&CPlayer::OnDestoryBoomEffect);
		
		CScene* currScene = CSceneMgr::GetInst()->GetCurrScene();
		currScene->AddObject(m_pBoomEffect, GROUP_TYPE::BOOM_EFFECT);
		currScene->DestroyGroup(GROUP_TYPE::MONSTER);
		currScene->DeleteGroup(GROUP_TYPE::PROJ_MONSTER);
	}
}

void CPlayer::UpdateMove()
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	CRigidBody* pRigid = GetRigidBody();
	Vector2 moveVec = Vector2(0.f, 0.f);
	Vector2 vColScale = GetCollider()->GetScale();

	if (KEY_HOLD(KEY::W) && 0 < m_vPos.y - vColScale.y)
	{
		moveVec += Vector2(0.f, -1.f);
	}
	if (KEY_HOLD(KEY::S) && vResolution.y > m_vPos.y + vColScale.y)
	{
		moveVec += Vector2(0.f, 1.f);
	}
	if (KEY_HOLD(KEY::A) && 0 < m_vPos.x - vColScale.x)
	{
		moveVec += Vector2(-1.f, 0.f);
	}
	if (KEY_HOLD(KEY::D) && vResolution.x > m_vPos.x + vColScale.x)
	{
		moveVec += Vector2(1.f, 0.f);
	}

	if(moveVec.Length() != 0.f)
		moveVec.Normalize();
	
	pRigid->SetVelocity(moveVec * m_fSpeed);
}

void CPlayer::UpdateAnimation()
{
	if (m_ePrevState == m_eCurrState && m_iPrevDir == m_iDir)
		return;

	switch (m_eCurrState)
	{
	case PLAYER_STATE::IDLE:
		GetAnimator()->Play(L"IDLE", true);
		break;
	case PLAYER_STATE::MOVE:
		if(m_iDir == 1)
			GetAnimator()->Play(L"MOVE_RIGHT", true);
		else if(m_iDir == -1)
			GetAnimator()->Play(L"MOVE_LEFT", true);
		break;
	case PLAYER_STATE::DEAD:
		GetAnimator()->Play(L"DEAD", false);
		break;
	}
}

void CPlayer::UpdateGravity()
{
	GetRigidBody()->AddForce(Vector2(0.f, 500.f));
}
 
void CPlayer::SummonSubUnit()
{
	CObject* pPlayerSubUnit = new CPlayerSubUnit(this, m_iPower - 4);
	pPlayerSubUnit->SetName(L"CPlayerSubUnit");
	pPlayerSubUnit->SetPos(m_vPos);
	CreateObject(pPlayerSubUnit, GROUP_TYPE::PLAYER_SUBUNIT);
}

void CPlayer::DestroyAllSubUnit()
{
	CSceneMgr::GetInst()->GetCurrScene()->DeleteGroup(GROUP_TYPE::PLAYER_SUBUNIT);
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (m_eCurrState == PLAYER_STATE::DEAD)
		return;

	CObject* pOtherObj = _pOther->GetObj();
	wstring name = pOtherObj->GetName();
	if (!m_bInvincibleState && (name == L"Monster" || name == L"Missile_Monster" || name == L"BossMonster"))
	{
		DestroyMine();
	}
	else if (name == L"PowerItem")
	{
		CSoundMgr::GetInst()->Play_SFX(L"ItemPickUp");

		m_iPower++;
		CGameMgr::GetInst()->AddGameScore(100);

		if (4 < m_iPower && m_iPower < 8)
			SummonSubUnit();
	}
	else if (name == L"BoomItem")
	{
		CSoundMgr::GetInst()->Play_SFX(L"ItemPickUp");

		CGameMgr::GetInst()->AddBoomCount();
		CGameMgr::GetInst()->AddGameScore(100);
	}
}

