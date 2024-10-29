#pragma once
#include "CObject.h"

enum class MISSILE_TYPE
{
	PLAYER_1 = 0,
	PLAYER_2 = 1,
	PLAYER_3 = 2,

	ENEMY_1 = 3,
	ENEMY_2 = 4,
	ENEMY_3 = 5,
	ENEMY_4 = 6,
};

class CMissile : 
	public CObject
{
private:
	MISSILE_TYPE	m_eType;
	CTexture*		m_pTex;
	Vector2			m_vDir;
	float			m_fSpeed;
	int				m_iDamage;

public:
	int GetDamage() { return m_iDamage; }

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	
public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMissile);
	
public:
	CMissile(MISSILE_TYPE _type, Vector2 _vPos, Vector2 _vDir);
	~CMissile();
};

