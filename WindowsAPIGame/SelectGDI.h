#pragma once
class SelectGDI
{
private:
	HDC hDC;
	HPEN hDefaultPen;
	HBRUSH hDefaultBrush;
	HFONT hDefaultFont;

public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _ePenType);
	SelectGDI(HDC _dc, const wstring _fontName, int _fontSize);
	~SelectGDI();
};

