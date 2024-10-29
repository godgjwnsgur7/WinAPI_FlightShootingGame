#pragma once

class CBossHpBarUI;
class CObject;

class CBossMonster :
	public CObject
{
	CBossHpBarUI* m_pHpBarUI;
	int		m_iHP;
	float	m_fHitTimer;
	float	m_fHitDurTime;
	bool	m_bHitState;

	int		m_iPatternNum;
	float	m_fPatternTimer;
	float	m_fSubPatternTimer;
	bool	m_bPatternState;

	int		m_iPatternSubNum;
	bool	m_bPatternTrigger;

private:
	void OnDamaged(int _damage);
	void UpdatePattern();
	bool Pattern1();
	bool Pattern2();
	bool Pattern3();
	bool Pattern4();
	bool Pattern5();

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void DestroyMine();

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	CLONE(CBossMonster);
	CBossMonster(int _iHP);
	~CBossMonster();
};

