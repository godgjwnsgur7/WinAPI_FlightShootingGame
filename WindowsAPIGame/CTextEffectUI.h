#pragma once

#include "CObject.h"

class CTextEffectUI :
	public CObject
{
	wstring m_textStr;
	int		m_iCurrEffectIndex; // 이펙트 현재 순서
	
	int		m_iSize;
	int		m_iMaxSize;
	
	int		m_iPrevSize;
	int		m_iCurrSize;
	float	m_fCurrTimer;

private:
	void TextSizeEffect(int _targetSize);

public:
	virtual void Update();
	virtual void Render(HDC _dc);

public:
	CLONE(CTextEffectUI);
	CTextEffectUI(const wstring _textStr, int _size, int _maxSize);
	~CTextEffectUI();
};