#pragma once

class CPlayer;
class CTextEffectUI;

struct tStageData
{
	float spawnPoint;
	int spawnTime;		
	int spawnMonsterId;
};

struct tGameInfo
{
	int life;
	int score;
	int boomCount;
};

class CGameMgr
{
	SINGLE(CGameMgr);

private:
	CPlayer* m_pPlayer;
	CTextEffectUI* m_pTextEffectUI;

	vector<tStageData> m_vecStageDatas;
	tGameInfo m_tGameInfo;

	float	m_fGameTimer;
	float	m_fCurrSpawnTime;
	int		m_iStageId;
	int		m_iSpawnIndex;
	int		m_iMaxScore;
	bool	m_bGameState;
	bool	m_bEffectState;
	bool	m_bGameOver;
	bool	m_bDebugMode;

	const int MAXSTAGE = 3;

private:
	void LoadStageData(int _stageId);
	
public:
	void LoadGameInfo();
	void SaveGameInfo();

public:
	void SetPlayer(CPlayer* _pPlayer) { m_pPlayer = _pPlayer; }
	CPlayer* GetPlayer() { return m_pPlayer; }

public:
	void AddGameScore(int _score) { m_tGameInfo.score += _score; }
	void SetBoomCount(int _count) { m_tGameInfo.boomCount = _count; }

public:
	bool IsDebugMode() { return m_bDebugMode; }
	bool IsGameState() { return m_bGameState; }
	bool IsGameOver() { return m_bGameOver; }
	int GetMaxScore() { return m_iMaxScore; }
	const tGameInfo GetGameInfo() { return m_tGameInfo; }

public:
	void AddBoomCount();
	bool IsUseBoom();
	bool IsUseLife();

public:
	void Init();
	void Update();
	void SpawnMonster(MONSTER_TYPE _eType, float _spawnPoint);

public:
	void StartGame();
	void StartStage(int _stageId);
	void ClearStage();
	void GameOver();
};

