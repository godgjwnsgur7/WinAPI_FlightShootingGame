#pragma once

class CPlayer;
class CObject;
class CTexture;

class CPlayerSubUnit :
	public CObject
{
	CPlayer*		m_pOwner;
	CTexture*		m_pTex;
	queue<Vector2>	m_qParentPos;

	int		m_iUnitId;
	float	m_fFollowDelay;
	float	m_fCurrAttackDelay;
	float	m_fAttackDelay;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

private:
	void UpdateMove();
	void UpdateState();
	void CreateMissile();

public:
	CLONE(CPlayerSubUnit);
	CPlayerSubUnit(CPlayer* _pOwner, int _iUnitId);
	~CPlayerSubUnit();
};

