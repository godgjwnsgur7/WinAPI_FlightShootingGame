#include "pch.h"
#include "CMonster.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CItem.h"

#include "CGameMgr.h"
#include "CTimeMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CCollider.h"
#include "CRigidBody.h"
#include "CTexture.h"
#include "CMissile.h"
#include "CExplosion.h"

CMonster::CMonster(MONSTER_TYPE _eType)
	: m_tInfo{}
	, m_eType(_eType)
	, m_pTex(nullptr)
	, m_bHitState(false)
	, m_fHitTimer(0.f)
	, m_fAttackDelayTime(2.f)
	, m_fAttackTimer(0.f)
	, m_bAttack(true)
	, m_bDropItem(true)
{
	CreateCollider();

	Vector2 vOffset = {};

	switch (m_eType)
	{
	case MONSTER_TYPE::ENEMY_S:
		m_vScale = Vector2(32.5f, 32.5f);
		break;
	case MONSTER_TYPE::ENEMY_M:
		m_vScale = Vector2(50.f, 70.f);
		break;
	case MONSTER_TYPE::ENEMY_L:
		m_vScale = Vector2(85.f, 80.f);
		break;
	}

	vOffset = Vector2(-2.f, 0.f);
	GetCollider()->SetScale(m_vScale);
	GetCollider()->SetOffsetPos(vOffset);
}

CMonster::~CMonster()
{

}

void CMonster::OnAttack()
{
	if (m_eType == MONSTER_TYPE::ENEMY_M || !m_bAttack)
		return;

	Vector2 vDir = CGameMgr::GetInst()->GetPlayer()->GetPos() - GetPos();
	vDir = vDir.Normalize();

	switch (m_eType)
	{
	case MONSTER_TYPE::ENEMY_S:
	{
		Vector2 vMissilePos = GetPos();
		vMissilePos.y += GetScale().y / 3.f;

		CMissile* pMissile = new CMissile(MISSILE_TYPE::ENEMY_2, vMissilePos, vDir);
		pMissile->SetName(L"Missile_Monster");
		CreateObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
	}
		break;
	case MONSTER_TYPE::ENEMY_L:
	{
		Vector2 vMissilePos1 = GetPos();
		vMissilePos1.x -= 20.f;
		vMissilePos1.y += GetScale().y / 2.f + 5.f;
		Vector2 vMissilePos2 = GetPos();
		vMissilePos2.x += 20.f;
		vMissilePos2.y += GetScale().y / 2.f + 5.f;

		CMissile* pMissile1 = new CMissile(MISSILE_TYPE::ENEMY_4, vMissilePos1, vDir);
		pMissile1->SetName(L"Missile_Monster");
		CreateObject(pMissile1, GROUP_TYPE::PROJ_MONSTER);
		
		CMissile* pMissile2 = new CMissile(MISSILE_TYPE::ENEMY_4, vMissilePos2, vDir);
		pMissile2->SetName(L"Missile_Monster");
		CreateObject(pMissile2, GROUP_TYPE::PROJ_MONSTER);
	}
		break;
	}
}

void CMonster::Update()
{
	if (m_bHitState)
	{
		m_fHitTimer += fDT;

		if (m_fHitTimer >= 0.05f)
		{
			m_bHitState = false;
			m_fHitTimer = 0.f;
		}
	}

	m_fAttackTimer += fDT;
	if (m_fAttackTimer >= m_fAttackDelayTime)
	{
		m_fAttackTimer -= m_fAttackDelayTime;
		OnAttack();
	}

	m_pRigidBody->SetVelocity(Vector2(0.f, m_tInfo.fSpeed));
}

void CMonster::Render(HDC _dc)
{
	UINT iWidth = 0;
	UINT iHeight = 0;
	Vector2 subPos = {};

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vector2 vScale = GetScale();

	switch (m_eType)
	{
	case MONSTER_TYPE::ENEMY_S:
		iWidth = 13;
		iHeight = 12;
		subPos = Vector2(125, 66);
		break;
	case MONSTER_TYPE::ENEMY_M:
		iWidth = 25;
		iHeight = 25;
		subPos = Vector2(100, 66);
		break;
	case MONSTER_TYPE::ENEMY_L:
		iWidth = 33;
		iHeight = 28;
		subPos = Vector2(67, 66);
		break;
	}

	if (m_bHitState)
		subPos += Vector2(0, 28);

	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth * 1.5f))
		, (int)(vRenderPos.y - (float)(iHeight * 1.5f))
		, iWidth * 3.f, iHeight * 3.f
		, m_pTex->GetDC()
		, subPos.x, subPos.y
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	ComponentRender(_dc);
}

void CMonster::OnDamaged(int _damage)
{
	m_tInfo.iHP -= _damage;

	if (m_tInfo.iHP <= 0)
	{
		DestroyMine();
	}
	else
	{
		m_bHitState = true;
	}
}

void CMonster::DestroyMine()
{
	if (m_bDropItem)
	{
		int random = rand();
		if (random % 100 <= 20)
		{
			CObject* pItem = new CItem(ITEM_TYPE::POWER, Vector2(m_vPos));
			pItem->SetName(L"PowerItem");
			CSceneMgr::GetInst()->GetCurrScene()->AddObject(pItem, GROUP_TYPE::ITEM);
		}
		else if (random % 100 <= 30)
		{
			CObject* pItem = new CItem(ITEM_TYPE::BOOM, Vector2(m_vPos));
			pItem->SetName(L"BoomItem");
			CSceneMgr::GetInst()->GetCurrScene()->AddObject(pItem, GROUP_TYPE::ITEM);
		}

		CExplosion* explosion = new CExplosion;
		explosion->SetPos(GetPos());

		switch (m_eType)
		{
		case MONSTER_TYPE::ENEMY_S:
			explosion->SetAnimScaleSize(1.5f);
			CGameMgr::GetInst()->AddGameScore(100);
			break;
		case MONSTER_TYPE::ENEMY_M:
			explosion->SetAnimScaleSize(3.f);
			CGameMgr::GetInst()->AddGameScore(150);
			break;
		case MONSTER_TYPE::ENEMY_L:
			explosion->SetAnimScaleSize(4.5f);
			CGameMgr::GetInst()->AddGameScore(200);
			break;
		}

		CreateObject(explosion, GROUP_TYPE::EXPLOSION_EFFECT);
	}
	
	DeleteObject(this);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	wstring name = pOtherObj->GetName();

	if (name == L"Missile_Player")
	{
		CMissile* missile = dynamic_cast<CMissile*>(pOtherObj);
		if (missile != nullptr)
		{
			OnDamaged(missile->GetDamage());
		}
	}
	else if (name == L"DesWall")
	{
		m_bDropItem = false;
		DestroyMine();
	}
	else if (name == L"DownColWall")
	{
		m_bAttack = false;
	}
}
