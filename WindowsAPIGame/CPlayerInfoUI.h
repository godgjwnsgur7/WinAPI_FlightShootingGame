#pragma once
#include "CUI.h"

class CTexture;
class CScoreTextUI;

class CPlayerInfoUI :
	public CUI
{
	CScoreTextUI* m_pScoreTextUI;
	CTexture* m_pLifeTex;
	CTexture* m_pBoomTex;

	int		m_iMaxCount;
	int		m_iCurrLifeCount;
	int		m_iCurrBoomCount;

	virtual void Update();
	virtual void Render(HDC _dc);

public:
	CLONE(CPlayerInfoUI);

	CPlayerInfoUI();
	~CPlayerInfoUI();
};
