#include "pch.h"
#include "CGameMgr.h"

#include "CCore.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CMonFactory.h"
#include "CBossMonster.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CTextEffectUI.h"
#include "CResMgr.h"
#include "CSound.h"

CGameMgr::CGameMgr()
	: m_pPlayer(nullptr)
	, m_tGameInfo{}
	, m_pTextEffectUI(nullptr)
	, m_fGameTimer(0.f)
	, m_fCurrSpawnTime(0.f)
	, m_iStageId(0)
	, m_iSpawnIndex(0)
	, m_bGameState(false) 
	, m_bEffectState(false)
	, m_bGameOver(false)
	, m_bDebugMode(false)
{

}

CGameMgr::~CGameMgr()
{
}

void CGameMgr::Init()
{
	m_tGameInfo;
	m_fGameTimer = 0.f;
	m_fCurrSpawnTime = 0.f;
	m_iStageId = 0;
	m_iSpawnIndex = 0;
	m_bGameState = false;
	m_bEffectState = false;
	m_bGameOver = false;
}

tStageData GetStageData(string str)
{
	tStageData data = {};
	vector<string> strs = Split(str, ' ');

	data.spawnPoint = stof(strs[0]);
	data.spawnTime = stoi(strs[1]);
	data.spawnMonsterId = stoi(strs[2]);
	
	return data;
}

void CGameMgr::LoadStageData(int _stageId)
{
	m_iStageId = _stageId;
	m_vecStageDatas.clear();

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"stage\\Stage";
	strFilePath += m_iStageId + '0';
	strFilePath += L".txt";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// animation 이름 읽기
	string str;
	char szBuff[256] = {};
	FScanf(szBuff, pFile);
	str = szBuff;

	while (str != "End\r")
	{
		m_vecStageDatas.push_back(GetStageData(str));
		FScanf(szBuff, pFile);
		str = szBuff;
	}
	
	fclose(pFile);
}

void CGameMgr::LoadGameInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"stage\\GameInfo.txt";

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	string str;
	char szBuff[256] = {};
	FScanf(szBuff, pFile);
	str = szBuff;

	m_iMaxScore = std::stoi(str);
	fclose(pFile);
}

void CGameMgr::SaveGameInfo()
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"stage\\GameInfo.txt";

	if (m_tGameInfo.score > m_iMaxScore)
		m_iMaxScore = m_tGameInfo.score;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");
	assert(pFile);

	fprintf(pFile, "%d\n", m_iMaxScore);

	fclose(pFile);
}

void CGameMgr::SpawnMonster(MONSTER_TYPE _eType, float _spawnPoint)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();

	CMonster* pMon1 = CMonFactory::CreateMonster(_eType
		, Vector2((vResolution.x / 2) + (_spawnPoint * 50.f), -100.f)); 
	pMon1->SetName(L"Monster");
	
	CSceneMgr::GetInst()->GetCurrScene()->AddObject(pMon1, GROUP_TYPE::MONSTER);
}

void CGameMgr::AddBoomCount()
{
	if (m_tGameInfo.boomCount < 3)
		m_tGameInfo.boomCount++;
}

bool CGameMgr::IsUseBoom()
{
	if (m_tGameInfo.boomCount > 0)
	{
		m_tGameInfo.boomCount--;
		return true;
	}

	return false;
}

bool CGameMgr::IsUseLife()
{
	m_tGameInfo.life--;

	if (m_tGameInfo.life > 0)
	{
		m_tGameInfo.boomCount = 1;
		return true;
	}

	m_bGameOver = true;
	return false;
}

void CGameMgr::Update()
{
	if (KEY_TAP(KEY::G))
	{
		m_bDebugMode = !m_bDebugMode;
	}

	if (m_bGameOver)
	{
		m_fGameTimer += fDT;

		if (m_fGameTimer > 1.f && !m_bEffectState)
		{
			GameOver();
		}
		else if (m_bEffectState && m_bGameOver)
		{
			if (m_pTextEffectUI != nullptr && m_pTextEffectUI->IsDead())
			{
				m_bGameOver = false;
				ChangeScene(SCENE_TYPE::RESULT);
			}
		}
		return;
	}

	if (m_bGameState == false)
	{
		m_fGameTimer += fDT;

		if (m_fGameTimer > 1.f && !m_bEffectState)
		{
			m_bEffectState = true;
			Vector2 vResolution = CCore::GetInst()->GetResolution();
			wstring str = L"Stage " + std::to_wstring(m_iStageId);
			m_pTextEffectUI = new CTextEffectUI(str, 50, 70);
			m_pTextEffectUI->SetPos(vResolution / 2.f);
			CSceneMgr::GetInst()->GetCurrScene()->AddObject((CObject*)m_pTextEffectUI, GROUP_TYPE::UI_OBJECT);
			
			CSoundMgr::GetInst()->Play_SFX(L"NextLevel");
		}
		else if (m_bEffectState)
		{
			if (m_pTextEffectUI != nullptr && m_pTextEffectUI->IsDead())
			{
				m_fGameTimer = 0.f;
				m_bEffectState = false;
				m_bGameState = true;
			}
		}
		return;
	}
	
	if (m_vecStageDatas.size() > m_iSpawnIndex)
	{
		m_fCurrSpawnTime += fDT;

		int i = m_iSpawnIndex;
		if (m_fCurrSpawnTime > m_vecStageDatas[i].spawnTime)
		{
			SpawnMonster((MONSTER_TYPE)m_vecStageDatas[i].spawnMonsterId, m_vecStageDatas[i].spawnPoint);
			m_fCurrSpawnTime = 0;
			m_iSpawnIndex++;

			if (m_iSpawnIndex == m_vecStageDatas.size())
			{
				CObject* pBossMonster = new CBossMonster(5000.f * m_iStageId);
				pBossMonster->SetName(L"BossMonster");
				pBossMonster->SetAnimScaleSize(4.f);
				CreateObject(pBossMonster, GROUP_TYPE::BOSSMONSTER);
			}
		}
	}
}

void CGameMgr::StartGame()
{
	Init();
	m_tGameInfo.life = 3;
	m_tGameInfo.score = 0;
	m_tGameInfo.boomCount = 1;
	LoadGameInfo();

	StartStage(1);
}

void CGameMgr::StartStage(int _stageId)
{
	LoadStageData(_stageId);
}

void CGameMgr::ClearStage()
{
	CSceneMgr::GetInst()->GetCurrScene()->DestroyGroup(GROUP_TYPE::MONSTER);
	CSceneMgr::GetInst()->GetCurrScene()->DeleteGroup(GROUP_TYPE::PROJ_MONSTER);
	
	m_bGameState = false;
	++m_iStageId;
	
	if (MAXSTAGE < m_iStageId)
		m_iStageId = MAXSTAGE;

	StartStage(m_iStageId);
}

void CGameMgr::GameOver()
{
	CSoundMgr::GetInst()->Play_SFX(L"GameOver");

	m_bEffectState = true;
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	wstring str = L"Game Over!!";
	m_pTextEffectUI = new CTextEffectUI(str, 50, 70);
	m_pTextEffectUI->SetPos(vResolution / 2.f);
	CSceneMgr::GetInst()->GetCurrScene()->AddObject((CObject*)m_pTextEffectUI, GROUP_TYPE::UI_OBJECT);
}
