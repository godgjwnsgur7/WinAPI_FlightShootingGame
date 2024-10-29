#include "pch.h"
#include "CBackgroundGroup.h"

#include "CBackground.h"
#include "CObject.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCore.h"

CBackgroundGroup::CBackgroundGroup()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();

	float fSpeed1 = 700.f;
	float fSpeed2 = 500.f;
	float fSpeed3 = 200.f;

	m_pBackground1_1 = new CBackground;
	CTexture* pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background1.bmp");
	m_pBackground1_1->SetTexture(pTex);
	m_pBackground1_1->SetSpeed(fSpeed1);

	m_pBackground1_2 = new CBackground;
	pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background1.bmp");
	m_pBackground1_2->SetTexture(pTex);
	m_pBackground1_2->SetSpeed(fSpeed1);

	m_pBackground2_1 = new CBackground;
	pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background2.bmp");
	m_pBackground2_1->SetTexture(pTex);
	m_pBackground2_1->SetSpeed(fSpeed2);

	m_pBackground2_2 = new CBackground;
	pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background2.bmp");
	m_pBackground2_2->SetTexture(pTex);
	m_pBackground2_2->SetSpeed(fSpeed2);

	m_pBackground3_1 = new CBackground;
	pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background3.bmp");
	m_pBackground3_1->SetTexture(pTex);
	m_pBackground3_1->SetSpeed(fSpeed3);

	m_pBackground3_2 = new CBackground;
	pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Background3.bmp");
	m_pBackground3_2->SetTexture(pTex);
	m_pBackground3_2->SetSpeed(fSpeed3);
}

CBackgroundGroup::~CBackgroundGroup()
{
	if (nullptr != m_pBackground1_1) delete m_pBackground1_1;
	if (nullptr != m_pBackground1_2) delete m_pBackground1_2;
	if (nullptr != m_pBackground2_1) delete m_pBackground2_1;
	if (nullptr != m_pBackground2_2) delete m_pBackground2_2;
	if (nullptr != m_pBackground3_1) delete m_pBackground3_1;
	if (nullptr != m_pBackground3_2) delete m_pBackground3_2;
}

void CBackgroundGroup::CheckParallax(CBackground* m_pBackground1, CBackground* m_pBackground2)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	
	if (m_pBackground1->GetPos().y - (m_vScale.y / 2.f) > vResolution.y)
	{
		Vector2 vec = m_pBackground2->GetPos() - Vector2(0.f, m_vScale.y);
		m_pBackground1->SetPos(vec);
	}
	else if (m_pBackground2->GetPos().y - (m_vScale.y / 2.f) > vResolution.y)
	{
		Vector2 vec = m_pBackground1->GetPos() - Vector2(0.f, m_vScale.y);
		m_pBackground2->SetPos(vec);
	}
}

void CBackgroundGroup::SetPos(Vector2 _vPos)
{
	m_vPos = _vPos;
	m_pBackground1_1->SetPos(_vPos);
	m_pBackground2_1->SetPos(_vPos);
	m_pBackground3_1->SetPos(_vPos);

	Vector2 _vUpPos = _vPos - Vector2(0.f, m_vScale.y);
	m_pBackground1_2->SetPos(_vUpPos);
	m_pBackground2_2->SetPos(_vUpPos);
	m_pBackground3_2->SetPos(_vUpPos);
}

void CBackgroundGroup::SetScale(Vector2 _vScale)
{
	m_vScale = _vScale;
	m_pBackground1_1->SetScale(_vScale);
	m_pBackground2_1->SetScale(_vScale);
	m_pBackground3_1->SetScale(_vScale);
	m_pBackground1_2->SetScale(_vScale);
	m_pBackground2_2->SetScale(_vScale);
	m_pBackground3_2->SetScale(_vScale);
}

void CBackgroundGroup::Update()
{
	m_pBackground1_1->Update();
	m_pBackground1_2->Update();
	m_pBackground2_1->Update();
	m_pBackground2_2->Update();
	m_pBackground3_1->Update();
	m_pBackground3_2->Update();

	CheckParallax(m_pBackground1_1, m_pBackground1_2);
	CheckParallax(m_pBackground2_1, m_pBackground2_2);
	CheckParallax(m_pBackground3_1, m_pBackground3_2);
}

void CBackgroundGroup::Render(HDC _dc)
{
	m_pBackground1_1->Render(_dc);
	m_pBackground1_2->Render(_dc);
	m_pBackground2_1->Render(_dc);
	m_pBackground2_2->Render(_dc);
	m_pBackground3_1->Render(_dc);
	m_pBackground3_2->Render(_dc);
}
