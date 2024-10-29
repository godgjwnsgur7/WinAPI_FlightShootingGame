#include "pch.h"
#include "CPlayerSubUnit.h"

#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMissile.h"

#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"

CPlayerSubUnit::CPlayerSubUnit(CPlayer* _pOwner, int _iUnitId)
	: m_qParentPos{}
	, m_pOwner(_pOwner)
	, m_iUnitId(_iUnitId)
	, m_fCurrAttackDelay(0.f)
	, m_fAttackDelay(0.5f)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	m_pTex = new CTexture;
	m_pTex->Load(strFilePath + L"texture\\PlayerSubUnit.bmp");

	m_vScale = Vector2(25.f, 25.f);
}

CPlayerSubUnit::~CPlayerSubUnit()
{

}

void CPlayerSubUnit::UpdateMove()
{
	if (m_qParentPos.empty())
	{
		m_qParentPos.push(m_pOwner->GetPos());
		return;
	}

	Vector2 vPlayerPos = m_pOwner->GetPos();

	if ((int)vPlayerPos.x != (int)m_qParentPos.back().x ||
		(int)vPlayerPos.y != (int)m_qParentPos.back().y)
		m_qParentPos.push(vPlayerPos);

	if (m_qParentPos.size() > CTimeMgr::GetInst()->GetCurrFPS() / 4 * m_iUnitId)
	{
		Vector2 followPos = m_qParentPos.front();
		SetPos(followPos);
		m_qParentPos.pop();
	}
}

void CPlayerSubUnit::UpdateState()
{
	if (KEY_HOLD(KEY::SPACE))
	{
		m_fCurrAttackDelay += fDT;

		if (m_fCurrAttackDelay > m_fAttackDelay)
		{
			m_fCurrAttackDelay -= m_fAttackDelay;
			CreateMissile();
		}
	}
}

void CPlayerSubUnit::CreateMissile()
{
	Vector2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 3.f;

	CMissile* pMissile = new CMissile(MISSILE_TYPE::PLAYER_3
		, vMissilePos, Vector2(0.f, -1.f));
	pMissile->SetName(L"Missile_Player");
	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayerSubUnit::Update()
{
	UpdateMove();
	UpdateState();
}

void CPlayerSubUnit::Render(HDC _dc)
{
	UINT iWidth = (int)m_pTex->Width();
	UINT iHeight = (int)m_pTex->Height();

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vector2 vScale = GetScale();

	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth * 1.25f))
		, (int)(vRenderPos.y - (float)(iHeight * 1.25f))
		, iWidth * 2.5f, iHeight * 2.5f
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	ComponentRender(_dc);
}
