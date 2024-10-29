#include "pch.h"
#include "CBackground.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"

#include "CTimeMgr.h"

CBackground::CBackground()
	: m_fSpeed(0.f)
{
}

CBackground::~CBackground()
{
	if (nullptr != m_pTex)
		delete m_pTex;
}

void CBackground::Update()
{
	if(m_fSpeed > 0.f)
		m_vPos += Vector2(0.f, m_fSpeed) * fDT;
}

void CBackground::Render(HDC _dc)
{
	UINT iWidth = (int)m_pTex->Width();
	UINT iHeight = (int)m_pTex->Height();

	Vector2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vector2 vScale = GetScale();

	TransparentBlt(_dc
		, (int)(vRenderPos.x - (float)(iWidth * 2.f))
		, (int)(vRenderPos.y - (float)(iHeight * 2.f))
		, iWidth * 4.f, iHeight * 4.f
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255)
	);
}
