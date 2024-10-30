#include "pch.h"
#include "CExplosion.h"

#include "CResMgr.h"

#include "CTexture.h"
#include "CAnimator.h"

CExplosion::CExplosion()
{
	CTexture* pExplosionTex = CResMgr::GetInst()->LoadTexture(L"Explosion", L"texture\\Explosion.bmp");

	CreateAnimator();

	GetAnimator()->CreateAnimation(L"Explosion1", pExplosionTex
		, Vector2(0.f, 0.f), Vector2(24.f, 24.f), Vector2(25.f, 25.f), 0.1f, 3);
	GetAnimator()->CreateAnimation(L"Explosion2", pExplosionTex
		, Vector2(0.f, 25.f), Vector2(24.f, 24.f), Vector2(25.f, 25.f), 0.1f, 3);
	
	GetAnimator()->Play(L"Explosion1", false);
}

CExplosion::~CExplosion()
{
}

void CExplosion::Update()
{
	if (GetAnimator()->IsFinishAnim())
	{
		if (GetAnimator()->GetCurrAnimName() == L"Explosion1")
			GetAnimator()->Play(L"Explosion2", false);
		else
		{
			DeleteObject(this);
		}
	}
}

void CExplosion::Render(HDC _dc)
{
	ComponentRender(_dc);
}
