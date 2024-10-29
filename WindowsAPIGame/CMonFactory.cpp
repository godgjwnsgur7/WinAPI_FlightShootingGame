#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"
#include "CMonster.h"
#include "CTexture.h"

#include "CPathMgr.h"

CMonster* CMonFactory::CreateMonster(MONSTER_TYPE _eType, Vector2 _vPos)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	CTexture* pTex = new CTexture;
	pTex->Load(strFilePath + L"texture\\Monsters.bmp");

	CMonster* pMon = nullptr;
	pMon = new CMonster(_eType);
	pMon->SetPos(_vPos);
	pMon->SetTexture(pTex);
	
	switch (_eType)
	{
	case MONSTER_TYPE::ENEMY_S:
	{
		tMonInfo info = {};
		info.iHP = 30.f;
		info.fSpeed = 150.f;
		pMon->SetMonInfo(info);
	}
		break;
	case MONSTER_TYPE::ENEMY_M:
	{
		tMonInfo info = {};
		info.iHP = 70.f;
		info.fSpeed = 750.f;
		pMon->SetMonInfo(info);
	}
		break;
	case MONSTER_TYPE::ENEMY_L:
	{
		tMonInfo info = {};
		info.iHP = 150.f;
		info.fSpeed = 100.f;
		pMon->SetMonInfo(info);
	}
		break;
	}

	pMon->CreateRigidBody();

	assert(pMon);

	return pMon;
}
