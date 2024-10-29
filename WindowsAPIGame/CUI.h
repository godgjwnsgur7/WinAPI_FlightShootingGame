#pragma once
#include "CObject.h"

class CUI 
	: public CObject
{
protected:
	vector<CUI*>	m_vecChildUI;
	CUI*			m_pParentUI;
	Vector2			m_vFinalPos;

	bool			m_bCamAffected; 
	bool			m_bMouseOn;	
	bool			m_bLbtnDown;

public:
	Vector2 GetFinalPos() { return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }

	void AddChild(CUI* _pUI);
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void SetDead();

protected:
	void Update_Child();
	void FinalUpdate_Child();
	void Render_Child(HDC _dc);

	void MouseOnCheck();

public:
	virtual void MouseOn();

	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	virtual CUI* Clone() = 0;

public:
	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	virtual ~CUI();

	friend class CUIMgr;
};