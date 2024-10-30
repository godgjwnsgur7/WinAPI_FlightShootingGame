#include "pch.h"
#include "CBoomEffect.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CTimeMgr.h"

#include "CTexture.h"
#include "CAnimator.h"
#include "CCollider.h"

CBoomEffect::CBoomEffect()
	: m_fCurrTime(0.f)
	, m_fEffectTime(1.5f)
	, m_pPlayerFunc(nullptr)
	, m_pPlayerInst(nullptr)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	SetPos(vResolution / 2.f);

	CTexture* pBoomEffectTex = CResMgr::GetInst()->LoadTexture(L"Boom", L"texture\\Boom.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"BoomEffect", pBoomEffectTex
		, Vector2(0.f, 0.f), Vector2(72.f, 72.f), Vector2(73.f, 72.f), 0.02f, 3);
	GetAnimator()->Play(L"BoomEffect", true);
}

CBoomEffect::~CBoomEffect()
{

}

void CBoomEffect::Update()
{
	m_fCurrTime += fDT;

	if (m_fCurrTime >= m_fEffectTime)
	{
		m_fCurrTime = 0.f;
		if (m_pPlayerInst && m_pPlayerFunc)
		{
			((*m_pPlayerInst).*m_pPlayerFunc)();
		}
	}
}

void CBoomEffect::Render(HDC _dc)
{
	ComponentRender(_dc);
}
