#pragma once

#include "CObject.h"

class CItem :
	public CObject
{
	ITEM_TYPE	m_eType;
	Vector2		m_vDir;
	float		m_fSpeed;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void OnCollisionEnter(CCollider* _pOther);

public:
	CLONE(CItem);

	CItem(ITEM_TYPE _eType, Vector2 _vPos);
	~CItem();
};

