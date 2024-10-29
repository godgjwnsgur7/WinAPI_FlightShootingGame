#include "pch.h"
#include "SelectGDI.h"

#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType) : hDC(_dc), hDefaultPen(nullptr), hDefaultBrush(nullptr), hDefaultFont(nullptr)
{
	HPEN hPen = CCore::GetInst()->GetPen(_ePenType);
	hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _ePenType) : hDC(_dc), hDefaultPen(nullptr), hDefaultBrush(nullptr), hDefaultFont(nullptr)
{
	HBRUSH hBrush = CCore::GetInst()->GetBrush(_ePenType);
	hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
} 

SelectGDI::SelectGDI(HDC _dc, const wstring _fontName, int _fontSize) : hDC(_dc), hDefaultPen(nullptr), hDefaultBrush(nullptr), hDefaultFont(nullptr)
{
	HFONT font = CreateFont(_fontSize, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_ROMAN, _fontName.c_str());
	hDefaultFont = (HFONT)SelectObject(_dc, font);
	DeleteObject(font);
}

SelectGDI::~SelectGDI()
{
	SelectObject(hDC, hDefaultPen);
	SelectObject(hDC, hDefaultBrush);
	SelectObject(hDC, hDefaultFont);
}
