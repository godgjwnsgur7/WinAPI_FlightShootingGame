#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{
	for (UINT i = 0; i < vecDead.size(); ++i)
	{
		delete vecDead[i];
	}		
	vecDead.clear();
	vecDead.shrink_to_fit();

	for (UINT i = 0; i < vecEvent.size(); ++i)
	{
		Excute(vecEvent[i]);
	}
	vecEvent.clear();
	vecEvent.shrink_to_fit();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurrScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		CObject* pDeadObj = (CObject*)_eve.lParam;
		if (pDeadObj->IsDead())
			return;
		pDeadObj->SetDead();
		vecDead.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	break;
	}

}
