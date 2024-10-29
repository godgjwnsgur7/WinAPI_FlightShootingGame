#pragma once

class CObject;

class CTextUI :
	public CObject
{
	wstring	m_textStr;
	int		m_iTextSize;

public:
	void SetTextStr(wstring _textStr) { m_textStr = _textStr; }

public:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	CLONE(CTextUI);
	CTextUI(wstring _textStr, int _iTextSize);
	~CTextUI();
};

