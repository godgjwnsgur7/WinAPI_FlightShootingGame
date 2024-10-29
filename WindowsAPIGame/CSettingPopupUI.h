#pragma once

#include "CPopupUI.h"
#include "CSettingPopupUI.h"

class CTextUI;
class CSliderUI;

class CSettingPopupUI :
	public CPopupUI
{
	CTextUI* m_pTitleTextUI;
	CTextUI* m_pBgmTextUI;
	CTextUI* m_pBgmValueTextUI;
	CTextUI* m_pSfxTextUI;
	CTextUI* m_pSfxValueTextUI;

public:
	void OnChangedBgmVolume(float _f);
	void OnChangedSfxVolume(float _f);

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();

	CLONE(CSettingPopupUI);
public:
	CSettingPopupUI();
	~CSettingPopupUI();
};

