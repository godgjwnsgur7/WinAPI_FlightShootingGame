#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CCollider.h"
#include "CTexture.h"

CMissile::CMissile(MISSILE_TYPE _type, Vector2 _vPos, Vector2 _vDir)
	: m_iDamage(10)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	m_pTex = new CTexture;
	m_pTex->Load(strFilePath + L"texture\\Missiles.bmp");

	m_eType = _type;
	m_vPos = _vPos;
	m_vDir = _vDir;

	m_vDir.Normalize();
	CreateCollider();

	Vector2 _vScale;
	Vector2 _vOffsetPos;
	switch (m_eType)
	{
	case MISSILE_TYPE::PLAYER_1: m_fSpeed = 700.f; m_iDamage = 10; _vScale = Vector2(12.5f, 20.f); _vOffsetPos = Vector2(0.f, -7.5f); break;
	case MISSILE_TYPE::PLAYER_2: m_fSpeed = 700.f; m_iDamage = 30; _vScale = Vector2(20.f, 25.f); _vOffsetPos = Vector2(0.f, -5.f); break;
	case MISSILE_TYPE::PLAYER_3: m_fSpeed = 700.f; m_iDamage = 15; _vScale = Vector2(12.5f, 37.5f); _vOffsetPos = Vector2(0.f, 0.f); break;
	case MISSILE_TYPE::ENEMY_1:	m_fSpeed = 1000.f; _vScale = Vector2(20.f, 30.f); _vOffsetPos = Vector2(0.f, -4.f); break;
	case MISSILE_TYPE::ENEMY_2:	m_fSpeed = 400.f; _vScale = Vector2(20.f, 25.f); _vOffsetPos = Vector2(0.f, -5.f); break;
	case MISSILE_TYPE::ENEMY_3:	m_fSpeed = 800.f; _vScale = Vector2(12.5f, 40.f); _vOffsetPos = Vector2(0.f, 0.f); break;
	case MISSILE_TYPE::ENEMY_4:	m_fSpeed = 700.f; _vScale = Vector2(30.f, 30.f); _vOffsetPos = Vector2(0.f, -2.5f); break;
	default:
		_vScale = Vector2(20.f, 20.f);
		break;
	}

	GetCollider()->SetScale(_vScale);
	GetCollider()->SetOffsetPos(_vOffsetPos);
}

CMissile::~CMissile()
{

}

void CMissile::Update()
{
	Vector2 vPos = GetPos();

	vPos.x += m_fSpeed * m_vDir.x * fDT;
	vPos.y += m_fSpeed * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	UINT iWidth = 10;
	UINT iHeight = 12;

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vector2 vScale = GetScale();
	
	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth * 1.5f))
		, (int)(vRenderPos.y - (float)(iHeight * 1.5f))
		, iWidth * 3.f, iHeight * 3.f
		, m_pTex->GetDC()
		, iWidth * (int)m_eType + (int)m_eType, 0
		, iWidth, iHeight
		, RGB(255, 0, 255)
	);

	ComponentRender(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	wstring name = pOtherObj->GetName();
	
	if (name == L"Monster" || name == L"DesWall" || name == L"Player" || name == L"BossMonster")
	{
		DeleteObject(this);
	}
}
