#pragma once
#include "CScene.h"

class CScene_Start : 
	public CScene
{
private:
	Vector2	m_vForcePos;
	float	m_fForceRadius;
	float	m_fCurrRadius;
	float	m_fForce;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void Enter();
	virtual void Exit();

public:
	void CreateForce();

public:
	CScene_Start();
	~CScene_Start();
};

