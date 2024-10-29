#pragma once

#include "CObject.h"

class CScoreTextUI :
	public CObject
{
private:
	UINT	m_iScore;

public:
	void SetScore(int _iScore) { m_iScore = _iScore; }

public:
	virtual void Update() {}
	virtual void Render(HDC _dc);

public:
	CLONE(CScoreTextUI);
	CScoreTextUI();
	~CScoreTextUI();
};

