#include "pch.h"
#include "CEventMgr.h"

#include "CObject.h"
#include "CUIMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
	: vecDead{}
	, vecEvent{}
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::Update()
{ 
	for (int i = vecDead.size() - 1; i >= 0; i--)
	{
		if(vecDead[i]->IsDead())
			delete vecDead[i];
	}		
	vecDead.clear();

	for (int i = 0; i < vecEvent.size(); i++)
	{
		Excute(vecEvent[i]);
	}
	vecEvent.clear();
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
		if (pDeadObj == nullptr && pDeadObj->IsDead())
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
