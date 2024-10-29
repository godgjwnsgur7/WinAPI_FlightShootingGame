#pragma once

class CBackground;

class CBackgroundGroup
	: public CObject
{
protected:
	CBackground* m_pBackground1_1;
	CBackground* m_pBackground1_2;
	CBackground* m_pBackground2_1;
	CBackground* m_pBackground2_2;
	CBackground* m_pBackground3_1;
	CBackground* m_pBackground3_2;

private:
	void CheckParallax(CBackground* m_pBackground1, CBackground* m_pBackground2);

public:
	virtual void SetPos(Vector2 _vPos);
	virtual void SetScale(Vector2 _vScale);
	
	virtual void Update();
	virtual void Render(HDC _dc);

	CLONE(CBackgroundGroup);
public:
	CBackgroundGroup();
	~CBackgroundGroup();
};

