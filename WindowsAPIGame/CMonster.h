#pragma once
#include "CObject.h"

struct tMonInfo
{
	int iHP;
	float fSpeed;
};

class CTexture; 

class CMonster 
	: public CObject
{
private:
	MONSTER_TYPE m_eType;
	tMonInfo	m_tInfo;
	Vector2		m_vDir;
	CTexture*	m_pTex;

	float		m_fAttackDelayTime;
	float		m_fAttackTimer;
	float		m_fHitTimer;
	bool		m_bHitState;
	bool		m_bAttack;
	bool		m_bDropItem;

public:
	float GetSpeed() { return m_tInfo.fSpeed; }
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void SetDir(Vector2 _vDir) { m_vDir = _vDir; }
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	const tMonInfo& GetInfo() { return m_tInfo; }

private:
	void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
	void OnDamaged(int _damage);
	virtual void DestroyMine();
	void OnAttack();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMonster);
public:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	CMonster(MONSTER_TYPE _eType);
	~CMonster();

	friend class CMonFactory;
};
