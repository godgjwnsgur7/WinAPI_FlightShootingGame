#pragma once
#include "CUI.h"

class CPopupUI :
	public CUI
{
private:
	Vector2 vDragStart;

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();

	CLONE(CPopupUI);
public:
	CPopupUI();
	~CPopupUI();
};