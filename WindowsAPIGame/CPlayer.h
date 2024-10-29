#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	DEAD,
};

enum class PLAYER_ATTACK_STATE
{
	NORMAL_ATTACK_1,
	NORMAL_ATTACK_2, 
	NORMAL_ATTACK_3,

	SKKIL_ATTACK_1,
};

class CTexture;
class CBoomEffect;

class CPlayer : 
	public CObject
{
private:
	vector<CObject*>	m_vecColObj;
	CBoomEffect*		m_pBoomEffect;

	PLAYER_STATE		m_eCurrState;
	PLAYER_STATE		m_ePrevState;
	int					m_iDir;
	int					m_iPrevDir;
	int					m_iPower;
	float				m_fSpeed;
	float				m_fAttackDelay;
	float				m_fCurrAttackDelay;
	float				m_fTimer;
	bool				m_bInvincibleState;

public:
	void OnDestoryBoomEffect();

public:
	virtual void Update();
	virtual void Render(HDC _dc);

private:
	void CreateMissile();
	void DestroyMine();

	void UpdateState();
	void UpdateMove();
	void UpdateAnimation();
	void UpdateGravity();

	void SummonSubUnit();
	void DestroyAllSubUnit();

	virtual void OnCollisionEnter(CCollider* _pOther);
	
	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();

	friend class CPlayerSubUnit;
};

