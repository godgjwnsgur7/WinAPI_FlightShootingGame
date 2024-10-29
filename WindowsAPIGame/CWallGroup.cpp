#include "pch.h"
#include "CWallGroup.h"

#include "CCore.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
#include "CWall.h"
#include "CCollisionWall.h"
#include "CDestructionWall.h"

CWallGroup::CWallGroup()
{
	CScene* currScene = CSceneMgr::GetInst()->GetCurrScene();

	Vector2 vResolution = CCore::GetInst()->GetResolution();
	float fColWallDistance = 25.f;
	float fDesWallDistance = 100.f;
	float fScale = 5.f;

	m_pLeftColWall = new CCollisionWall();
	m_pLeftColWall->SetPos(Vector2(-fColWallDistance, vResolution.y / 2.f));
	m_pLeftColWall->SetColliderScale(Vector2(fColWallDistance * 2.f, vResolution.y));
	m_pLeftColWall->SetName(L"LeftColWall");
	currScene->AddObject(m_pLeftColWall, GROUP_TYPE::WALL);

	m_pRightColWall = new CCollisionWall();
	m_pRightColWall->SetPos(Vector2(vResolution.x + fColWallDistance, vResolution.y / 2.f));
	m_pRightColWall->SetColliderScale(Vector2(fColWallDistance * 2.f, vResolution.y));
	m_pRightColWall->SetName(L"RightColWall");
	currScene->AddObject(m_pRightColWall, GROUP_TYPE::WALL);
	
	m_pUpColWall = new CCollisionWall();
	m_pUpColWall->SetPos(Vector2(vResolution.x / 2.f, -fColWallDistance));
	m_pUpColWall->SetColliderScale(Vector2(vResolution.x, fColWallDistance * 2.f));
	m_pUpColWall->SetName(L"UpColWall");
	currScene->AddObject(m_pUpColWall, GROUP_TYPE::WALL);
	
	m_pDownColWall = new CCollisionWall();
	m_pDownColWall->SetPos(Vector2(vResolution.x / 2.f, vResolution.y + fColWallDistance));
	m_pDownColWall->SetColliderScale(Vector2(vResolution.x, fColWallDistance * 2.f));
	m_pDownColWall->SetName(L"DownColWall");
	currScene->AddObject(m_pDownColWall, GROUP_TYPE::WALL);


	m_pLeftDesWall = new CDestructionWall();
	m_pLeftDesWall->SetPos(Vector2(-fDesWallDistance, vResolution.y / 2.f));
	m_pLeftDesWall->SetColliderScale(Vector2(fScale, vResolution.y * 2.f));
	m_pLeftDesWall->SetName(L"DesWall");
	currScene->AddObject(m_pLeftDesWall, GROUP_TYPE::WALL);
	
	m_pRightDesWall = new CDestructionWall();
	m_pRightDesWall->SetPos(Vector2(vResolution.x + fDesWallDistance, vResolution.y / 2.f));
	m_pRightDesWall->SetColliderScale(Vector2(fScale, vResolution.y * 2.f));
	m_pRightDesWall->SetName(L"DesWall");
	currScene->AddObject(m_pRightDesWall, GROUP_TYPE::WALL);
	
	m_pUpDesWall = new CDestructionWall();
	m_pUpDesWall->SetPos(Vector2(vResolution.x / 2.f, -fDesWallDistance * 5.f));
	m_pUpDesWall->SetColliderScale(Vector2(vResolution.x * 1.5f, fScale));
	m_pUpDesWall->SetName(L"DesWall");
	currScene->AddObject(m_pUpDesWall, GROUP_TYPE::WALL);
	
	m_pDownDesWall = new CDestructionWall();
	m_pDownDesWall->SetPos(Vector2(vResolution.x / 2.f, vResolution.y + fDesWallDistance));
	m_pDownDesWall->SetColliderScale(Vector2(vResolution.x * 1.5f, fScale));
	m_pDownDesWall->SetName(L"DesWall");
	currScene->AddObject(m_pDownDesWall, GROUP_TYPE::WALL);
}

CWallGroup::~CWallGroup()
{
	if (nullptr != m_pLeftColWall) delete m_pLeftColWall;
	if (nullptr != m_pRightColWall) delete m_pRightColWall;
	if (nullptr != m_pUpColWall) delete m_pUpColWall;
	if (nullptr != m_pDownColWall) delete m_pDownColWall;

	if (nullptr != m_pLeftDesWall) delete m_pLeftDesWall;
	if (nullptr != m_pRightDesWall) delete m_pRightDesWall;
	if (nullptr != m_pUpDesWall) delete m_pUpDesWall;
	if (nullptr != m_pDownDesWall) delete m_pDownDesWall;
}
