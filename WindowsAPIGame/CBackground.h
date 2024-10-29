#pragma once

class CTexture;
class CObject;

class CBackground
	: public CObject
{
	CTexture* m_pTex;
	float m_fSpeed;

public:
	void SetTexture(CTexture* _pTex) { m_pTex = _pTex; }
	void SetSpeed(float _f) { m_fSpeed = _f; }

public:
	virtual void Update();
	virtual void Render(HDC _dc);

	void AddPos(Vector2 _vPos) { m_vPos += _vPos; }

	CLONE(CBackground);
public:
	CBackground();
	~CBackground();
};

