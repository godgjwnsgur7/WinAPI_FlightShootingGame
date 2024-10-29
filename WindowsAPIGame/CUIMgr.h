#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;

public:
	void Update();

	void SetFocusedUI(CUI* _pUI);

private:

	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);;
};