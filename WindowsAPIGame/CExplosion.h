#pragma once
#include "CObject.h"

class CExplosion : public CObject
{
public:
	virtual void Update();
	virtual void Render(HDC _dc);

	CLONE(CExplosion);

public:
	CExplosion();
	~CExplosion();
};

