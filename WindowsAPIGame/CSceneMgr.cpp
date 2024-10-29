#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_Title.h"
#include "CScene_Result.h"
#include "CEventMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

CSceneMgr::CSceneMgr() 
	: m_pCurrScene(nullptr)
	, m_arrScene{}
	, m_fCurrTime(0.f)
	, m_bSceneChange(false)
	, m_eNextScene(SCENE_TYPE::END)
{

}

CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void CSceneMgr::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	m_arrScene[(UINT)SCENE_TYPE::TITLE] = new CScene_Title;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Title Scene");

	m_arrScene[(UINT)SCENE_TYPE::RESULT] = new CScene_Result;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Result Scene");

	// ÇöÀç ¾À
	m_pCurrScene = m_arrScene[(UINT)SCENE_TYPE::TITLE];
	m_pCurrScene->Enter();
}	

void CSceneMgr::Update()
{
	if (m_bSceneChange)
	{
		m_fCurrTime += fDT;

		if (m_fCurrTime >= 1.f)
		{
			m_pCurrScene->Exit();
			m_pCurrScene = m_arrScene[(UINT)m_eNextScene];
			m_pCurrScene->Enter();

			m_fCurrTime = 0.f;
			m_bSceneChange = false;
			CCamera::GetInst()->FadeIn(1.f);
		}
	}

	m_pCurrScene->Update();
	m_pCurrScene->FinalUpdate();
}

void CSceneMgr::Render(HDC _dc)
{
	m_pCurrScene->Render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	m_eNextScene = _eNext;

	if (m_eNextScene == SCENE_TYPE::END)
		return;

	m_fCurrTime = 0.f;
	m_bSceneChange = true;
	CCamera::GetInst()->FadeOut(1.f);
}
