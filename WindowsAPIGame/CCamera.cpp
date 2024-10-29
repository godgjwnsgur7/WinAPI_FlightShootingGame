#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "CCore.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
	, m_pVeilTex(nullptr)
	, m_bFadeEffectState(false)
{
}

CCamera::~CCamera()
{
	
}

void CCamera::Init()
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	m_pVeilTex = CResMgr::GetInst()->CreateTexture(L"CameraVeil", (UINT)vResolution.x, (UINT)vResolution.y);
}

void CCamera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;
	
	// 화면
	CalDiff();
}

void CCamera::Render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurrTime += fDT;

	float fRatio = 0;
	fRatio = effect.fCurrTime / effect.fDuration;
	
	if (fRatio < 0.f)
		fRatio = 0.f;
	else if (fRatio > 1.f)
		fRatio = 1.f;
	
	int iAlpha = 0;

	switch (effect.eEffect)
	{
	case CAM_EFFECT::FADE_OUT:
		iAlpha = (int)(255.f * fRatio);
		break;
	case CAM_EFFECT::FADE_IN:
		iAlpha = (int)(255.f * (1.f - fRatio));
		break;
	}
	
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0; // AC_SRC_ALPHA;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC()
		, 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);

	// 효과 종료 조건
	if (effect.fDuration < effect.fCurrTime)
	{
		m_bFadeEffectState = false;
		m_listCamEffect.pop_front();
		return;
	}
}

void CCamera::CalDiff()
{
	m_fAccTime += fDT;
	
	if (m_fTime <= m_fAccTime)
	{
		m_vCurrLookAt = m_vLookAt;
	}
	else
	{
		Vector2 vLookDir = m_vLookAt - m_vPrevLookAt;

		if (!vLookDir.IsZero())
		{
			m_vCurrLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}
	}

	Vector2 vResolution = CCore::GetInst()->GetResolution();
	Vector2 vCenter = vResolution / 2;

	m_vDiff = m_vCurrLookAt - vCenter;
	m_vPrevLookAt = m_vCurrLookAt;
}
