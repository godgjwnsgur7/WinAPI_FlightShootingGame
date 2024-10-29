#pragma once

#include "CBtnUI.h"
#include "CSliderUI.h"

typedef void(CSliderUI::* SLIDER_MEMFUNC)(void);

class CSliderHandleUI :
	public CBtnUI
{
	SLIDER_MEMFUNC	m_pSliderFunc;
	CSliderUI*		m_pSliderInst;

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetClickedCallBack(CSliderUI* _pSlider, SLIDER_MEMFUNC _pSliderFunc)
	{
		m_pSliderInst = _pSlider;
		m_pSliderFunc = _pSliderFunc;
	}

public:
	CLONE(CSliderHandleUI);
	CSliderHandleUI();
	~CSliderHandleUI();

	friend class CSliderUI;
};

