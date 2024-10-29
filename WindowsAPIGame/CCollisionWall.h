#pragma once
#include "CWall.h"

class CCollisionWall :
	public CWall
{
public:
	virtual void Update() {}

	CLONE(CCollisionWall);
public:
	CCollisionWall();
	~CCollisionWall();
};

