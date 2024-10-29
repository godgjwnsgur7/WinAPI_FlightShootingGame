#include "pch.h"
#include "CBossMonster.h"

#include "CCore.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMissile.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

#include "CExplosion.h"
#include "CBossHpBarUI.h"
#include "CSound.h"

CBossMonster::CBossMonster(int _iHP)
	: m_iHP(_iHP)
	, m_pHpBarUI(nullptr)
	, m_fHitTimer(0.f)
	, m_fHitDurTime(0.05f)
	, m_bHitState(false)
	, m_iPatternNum(0)
	, m_fPatternTimer(0.f)
	, m_fSubPatternTimer(0.f)
	, m_bPatternState(false)
	, m_iPatternSubNum(45)
	, m_bPatternTrigger(false)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	SetPos(Vector2(vResolution.x / 2.f, -200.f));

	CreateRigidBody();

	CreateCollider();
	GetCollider()->SetScale(Vector2(250.f, 200.f));
	GetCollider()->SetOffsetPos(Vector2(0.f, -30.f));
	
	CTexture* pPlayerTex = CResMgr::GetInst()->LoadTexture(L"Monster", L"texture\\Monsters.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE", pPlayerTex, Vector2(0.f, 0.f), Vector2(66.f, 66.f), Vector2(67.f, 0.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"HIT", pPlayerTex, Vector2(0.f, 66.f), Vector2(66.f, 66.f), Vector2(0.f, 0.f), 0.1f, 1);
	GetAnimator()->Play(L"IDLE", true);

	CSoundMgr::GetInst()->Play_SFX(L"Boss");
}

CBossMonster::~CBossMonster()
{

}

void CBossMonster::OnDamaged(int _damage)
{
	m_iHP -= _damage;

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->SetCurrHp(m_iHP);

	if (m_iHP <= 0)
	{
		DestroyMine();
		return;
	}
		
	if (m_bHitState == false)
	{
		GetAnimator()->Play(L"HIT", true);
		m_fHitTimer = 0.f;
		m_bHitState = true;
	}
}

void CBossMonster::UpdatePattern()
{
	if (!m_bPatternState)
	{
		m_fPatternTimer += fDT;

		// 보스 패턴 간격
		if (m_fPatternTimer >= 2.5f)
		{
			m_iPatternNum++;
			if (m_iPatternNum > 4)
				m_iPatternNum = 0;

			m_fPatternTimer = 0.f;
			m_bPatternState = true;
		}
	}
	else
	{
		bool isEndPattern;
		m_fPatternTimer += fDT;
		m_fSubPatternTimer += fDT;

		switch (m_iPatternNum)
		{
		case 0:	isEndPattern = Pattern1(); break;
		case 1:	isEndPattern = Pattern2(); break;
		case 2:	isEndPattern = Pattern3(); break;
		case 3:	isEndPattern = Pattern4(); break;
		case 4:	isEndPattern = Pattern5(); break;
		}

		if (isEndPattern)
		{
			m_fPatternTimer = 0.f;
			m_fSubPatternTimer = 0.f;
			m_iPatternSubNum = 30;
			m_bPatternState = false;
		}
	}
}

bool CBossMonster::Pattern1()
{
	if (m_fPatternTimer < 4.f)
	{
		if (m_fSubPatternTimer >= 0.3f)
		{
			m_fSubPatternTimer -= 0.3f;
			m_bPatternTrigger = !m_bPatternTrigger;

			int i = 0;
			if (m_bPatternTrigger)
				i += 5;

			for (; i <= 360; i += 10)
			{
				CMissile* pMissile = new CMissile(MISSILE_TYPE::ENEMY_2
					, GetPos(), GetDirVec(i));
				pMissile->SetName(L"Missile_Monster");

				CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
			}
		}
		return false;
	}

	return true;
}

bool CBossMonster::Pattern2()
{
	if (m_fPatternTimer < 4.f)
	{
		if (m_fSubPatternTimer >= 0.75f)
		{
			m_fSubPatternTimer -= 0.75f;
			Vector2 playerPos = CGameMgr::GetInst()->GetPlayer()->GetPos();

			Vector2 missilePos = GetPos() + Vector2(-80.f, 100.f);
			Vector2 dirVec = playerPos - missilePos;
			CMissile* pMissile1 = new CMissile(MISSILE_TYPE::ENEMY_4, missilePos , dirVec.Normalize());
			pMissile1->SetName(L"Missile_Monster");
			CreateObject(pMissile1, GROUP_TYPE::PROJ_MONSTER);

			missilePos = GetPos() + Vector2(-60.f, 100.f);
			dirVec = playerPos - missilePos;
			CMissile* pMissile2 = new CMissile(MISSILE_TYPE::ENEMY_4, missilePos, dirVec.Normalize());
			pMissile2->SetName(L"Missile_Monster");
			CreateObject(pMissile2, GROUP_TYPE::PROJ_MONSTER);

			missilePos = GetPos() + Vector2(60.f, 100.f);
			dirVec = playerPos - missilePos;
			CMissile* pMissile3 = new CMissile(MISSILE_TYPE::ENEMY_4, missilePos, dirVec.Normalize());
			pMissile3->SetName(L"Missile_Monster");
			CreateObject(pMissile3, GROUP_TYPE::PROJ_MONSTER);

			missilePos = GetPos() + Vector2(80.f, 100.f);
			dirVec = playerPos - missilePos;
			CMissile* pMissile4 = new CMissile(MISSILE_TYPE::ENEMY_4, missilePos, dirVec.Normalize());
			pMissile4->SetName(L"Missile_Monster");
			CreateObject(pMissile4, GROUP_TYPE::PROJ_MONSTER);
		}
		return false;
	}

	return true;
}

bool CBossMonster::Pattern3()
{
	if (m_fPatternTimer < 5.f)
	{
		if (m_fSubPatternTimer >= 0.1f)
		{
			m_fSubPatternTimer -= 0.1f;

			if (!m_bPatternTrigger)
			{
				m_iPatternSubNum += 7;

				if (m_iPatternSubNum > 150)
				{
					m_iPatternSubNum = 150;
					m_bPatternTrigger = true;
				}
			}
			else
			{
				m_iPatternSubNum -= 7;

				if (m_iPatternSubNum < 30)
				{
					m_iPatternSubNum = 35;
					m_bPatternTrigger = false;
				}
			}

			CMissile* pMissile = new CMissile(MISSILE_TYPE::ENEMY_4
				, GetPos(), GetDirVec(m_iPatternSubNum));
			pMissile->SetName(L"Missile_Monster");
			CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
		}
		return false;
	}

	return true;
}

bool CBossMonster::Pattern4()
{
	if (m_fPatternTimer < 5.f)
	{
		if (m_fSubPatternTimer >= 0.05f)
		{
			m_fSubPatternTimer -= 0.05f;

			m_iPatternSubNum = rand() % 120;
			m_iPatternSubNum += 30;

			if (m_bPatternTrigger)
			{
				CMissile* pMissile = new CMissile(MISSILE_TYPE::ENEMY_4
					, GetPos(), GetDirVec(m_iPatternSubNum));
				pMissile->SetName(L"Missile_Monster");

				CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
			}
			else
			{
				CMissile* pMissile = new CMissile(MISSILE_TYPE::ENEMY_2
					, GetPos(), GetDirVec(m_iPatternSubNum));
				pMissile->SetName(L"Missile_Monster");

				CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
			}

			m_bPatternTrigger = !m_bPatternTrigger;
		}
		return false;
	}

	return true;
}

bool CBossMonster::Pattern5()
{
	if (m_fPatternTimer < 3.5f)
	{
		if (m_fSubPatternTimer >= 0.75f)
		{
			m_fSubPatternTimer -= 0.75f;
			m_bPatternTrigger = !m_bPatternTrigger;

			float spawnPoint = -7;
			if (m_bPatternTrigger)
				spawnPoint += 1.25f;

			for(; spawnPoint <= 7; spawnPoint += 2.5f)
				CGameMgr::GetInst()->SpawnMonster(MONSTER_TYPE::ENEMY_M, spawnPoint);
		}
		return false;
	}

	return true;
}

void CBossMonster::Update()
{
	if (CGameMgr::GetInst()->IsGameOver())
		return;

	if (m_pRigidBody != nullptr)
	{
		m_pRigidBody->SetVelocity(Vector2(0.f, 100.f));
		
		if (GetPos().y >= 250.f)
		{
			m_pHpBarUI = new CBossHpBarUI(m_iHP);
			CreateObject((CObject*)m_pHpBarUI, GROUP_TYPE::UI);

			delete m_pRigidBody;
			m_pRigidBody = nullptr;
		}
		return;
	}
	
	if (m_bHitState)
	{
		m_fHitTimer += fDT;

		if (m_fHitTimer >= m_fHitDurTime)
		{
			m_fHitTimer = 0.f;
			GetAnimator()->Play(L"IDLE", true);
			m_bHitState = false;
		}
	}

	UpdatePattern();
}

void CBossMonster::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CBossMonster::DestroyMine()
{
	CExplosion* explosion = new CExplosion;
	explosion->SetPos(GetPos());
	explosion->SetAnimScaleSize(8.f);
	CGameMgr::GetInst()->AddGameScore(10000);
	CGameMgr::GetInst()->ClearStage();

	CSoundMgr::GetInst()->Play_SFX(L"Destroy");
	CreateObject(explosion, GROUP_TYPE::EXPLOSION_EFFECT);
	DeleteObject(this);
}

void CBossMonster::OnCollisionEnter(CCollider* _pOther)
{
	if (m_pRigidBody != nullptr)
		return;

	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		CMissile* missile = dynamic_cast<CMissile*>(pOtherObj);
		if (missile != nullptr)
		{
			OnDamaged(missile->GetDamage());
		}
	}
}
