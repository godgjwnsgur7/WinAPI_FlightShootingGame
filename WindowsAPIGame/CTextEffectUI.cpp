#include "pch.h"
#include "CTextEffectUI.h"

#include "CTimeMgr.h"

#include "SelectGDI.h"

CTextEffectUI::CTextEffectUI(const wstring _textStr, int _size, int _maxSize)
	: m_iCurrSize(10)
	, m_iPrevSize(10)
	, m_fCurrTimer(0.f)
	, m_textStr(_textStr)
	, m_iSize(_size)
	, m_iMaxSize(_maxSize)
	, m_iCurrEffectIndex(0)
{

}

CTextEffectUI::~CTextEffectUI()
{
}

void CTextEffectUI::TextSizeEffect(int _targetSize)
{
	if (_targetSize > m_iPrevSize)
	{
		m_fCurrTimer += 5.f * fDT;
		if (m_fCurrTimer > 1.f)
			m_fCurrTimer = 1.f;

		int num = _targetSize - m_iPrevSize;
		num *= m_fCurrTimer;
		m_iCurrSize = m_iPrevSize + num;

		if (m_fCurrTimer == 1.f)
		{
			m_fCurrTimer = 0.f;
			m_iCurrSize = _targetSize;
			m_iPrevSize = _targetSize;
			m_iCurrEffectIndex++;
		}
	}
	else if (_targetSize < m_iPrevSize)
	{
		m_fCurrTimer += 5.f * fDT;
		if (m_fCurrTimer > 1.f)
			m_fCurrTimer = 1.f;

		int num = m_iPrevSize - _targetSize;
		num *= m_fCurrTimer;
		m_iCurrSize = m_iPrevSize - num;
		 
		if (m_fCurrTimer == 1.f)
		{
			m_fCurrTimer = 0.f;
			m_iCurrSize = _targetSize;
			m_iPrevSize = _targetSize;
			m_iCurrEffectIndex++;
		}
	}
}

void CTextEffectUI::Update()
{
	switch (m_iCurrEffectIndex)
	{
	case 0: TextSizeEffect(m_iMaxSize); break;
	case 1:	TextSizeEffect(m_iSize); break;
	case 2: // ´ë±â
	{
		m_fCurrTimer += 2.f * fDT;
		if (m_fCurrTimer > 1.f)
		{
			m_fCurrTimer = 0.f;
			m_iCurrEffectIndex++;
		}
	}
		break;
	case 3: TextSizeEffect(m_iMaxSize); break;
	case 4: TextSizeEffect(10); break;
	case 5: DeleteObject(this); break;
	}
}

void CTextEffectUI::Render(HDC _dc)
{
	SetTextAlign(_dc, TA_CENTER);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));

	SelectGDI font(_dc, L"±Ã¼­", m_iCurrSize);
	TextOut(_dc, m_vPos.x, m_vPos.y, m_textStr.c_str(), m_textStr.size());
}
