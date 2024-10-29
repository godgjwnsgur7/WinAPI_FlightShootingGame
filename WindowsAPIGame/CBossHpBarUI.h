#pragma once

class CBossHpBarUI :
	public CObject
{
	int		m_iMaxHp;
	int		m_iCurrHp;

private:
	void SetCurrHp(int _iCurrHp);

public:
	virtual void Update() {}
	virtual void Render(HDC _dc);

public:
	CLONE(CBossHpBarUI);

	CBossHpBarUI(int _iMaxHp);
	~CBossHpBarUI();
	
	friend class CBossMonster;
};

