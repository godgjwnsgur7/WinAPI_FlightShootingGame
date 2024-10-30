#include "pch.h"
#include "CItem.h"

#include "CResMgr.h"

#include "CObject.h"
#include "CCollider.h"
#include "CRigidBody.h"
#include "CAnimator.h"
#include "CAnimation.h"

CItem::CItem(ITEM_TYPE _eType, Vector2 _vPos)
	: m_vDir{}
	, m_fSpeed(100.f)
{
	m_vPos = _vPos;
	m_vDir.x = ((int)_vPos.x % 2 == 0) ? 1 : -1;
	m_vDir.y = ((int)_vPos.y % 2 == 0) ? 1 : -1;

	CreateCollider();
	m_vScale = Vector2(35.f, 20.f);
	GetCollider()->SetScale(m_vScale);
	GetCollider()->SetOffsetPos(Vector2(0.f, 2.5f));

	CreateRigidBody();

	CTexture* pItemTex = CResMgr::GetInst()->LoadTexture(L"Item", L"texture\\Items.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"ITEM", pItemTex, Vector2(0, (int)_eType * 16), Vector2(16, 16), Vector2(17, 17), 0.1f, 9);
	GetAnimator()->Play(L"ITEM", true);

	SetAnimScaleSize(2.5f);
}

CItem::~CItem()
{
}

void CItem::Update()
{
	m_pRigidBody->SetVelocity(m_vDir * m_fSpeed);
}

void CItem::Render(HDC _dc)
{
	ComponentRender(_dc);
}

void CItem::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	wstring name = pOtherObj->GetName();

	if (name == L"Player")
	{
		DeleteObject(this);
	}
	else if (name == L"LeftColWall")
	{
		m_vDir.x = 1;
	}
	else if (name == L"RightColWall")
	{
		m_vDir.x = -1;
	}
	else if (name == L"UpColWall")
	{
		m_vDir.y = 1;
	}
	else if (name == L"DownColWall")
	{
		m_vDir.y = -1;
	}
}
