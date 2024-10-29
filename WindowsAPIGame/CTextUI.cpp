#include "pch.h"
#include "CTextUI.h"

#include "CObject.h"
#include "SelectGDI.h"

CTextUI::CTextUI(wstring _textStr, int _iTextSize)
	: m_textStr(_textStr)
	, m_iTextSize(_iTextSize)
{
}

CTextUI::~CTextUI()
{
}

void CTextUI::Update()
{

}

void CTextUI::Render(HDC _dc)
{
	SetTextAlign(_dc, TA_CENTER);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	SelectGDI font(_dc, L"±Ã¼­", m_iTextSize);
	TextOut(_dc, m_vPos.x, m_vPos.y, m_textStr.c_str(), m_textStr.size());
}
