#pragma once

#include "CObject.h"

class CWall
	: public CObject
{
public:
	void SetColliderScale(Vector2 _vScale);
	void SetColliderOffSet(Vector2 _vOffset);

public:
	virtual void Update() {}
	virtual void Render(HDC _dc);

public:
	CLONE(CWall);

public:
	CWall();
	~CWall();
};

