#pragma once
#include "CObject.h"
#include "CPlayer.h"

typedef void (CPlayer::* PLAYER_MEMFUNC)(void);

class CBoomEffect : 
	public CObject
{
	float	m_fCurrTime;
	float	m_fEffectTime;

	PLAYER_MEMFUNC	m_pPlayerFunc;
	CPlayer*		m_pPlayerInst;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void SetDestroyCallBack(CPlayer* _pPlayerInst, PLAYER_MEMFUNC _pPlayerFunc)
	{
		m_pPlayerInst = _pPlayerInst;
		m_pPlayerFunc = _pPlayerFunc;
	}

public:
	CLONE(CBoomEffect);

	CBoomEffect();
	~CBoomEffect();
};

