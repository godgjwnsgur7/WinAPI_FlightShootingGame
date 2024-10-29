#pragma once

#include "CUI.h"
#include "CScene.h"
#include "CSliderHandleUI.h"
#include "CSettingPopupUI.h"

typedef void (CSettingPopupUI::* SETTINGPOPUP_MEMFUNC)(float);

class CSliderUI :
	public CUI
{
private:
	CSliderHandleUI* m_pHandleUI;
	float	m_fSliderValue;
	bool	m_bMouseClickState;

	SETTINGPOPUP_MEMFUNC	m_pSettingPopupFunc;
	CSettingPopupUI*		m_pSettingPopupInst;

public:
	void OnChangedValue();
	void SetSliderValue(float _f);

public:
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	void SetValueChangedCallBack(CSettingPopupUI* _pSettingPopup, SETTINGPOPUP_MEMFUNC _pSettingPopupFunc)
	{
		m_pSettingPopupInst = _pSettingPopup;
		m_pSettingPopupFunc = _pSettingPopupFunc;
	}

	CLONE(CSliderUI);
public:
	CSliderUI(Vector2 _vScale, Vector2 _vPos);
	~CSliderUI();
};

