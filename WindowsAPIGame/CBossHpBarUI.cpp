#include "pch.h"
#include "CBossHpBarUI.h"

#include "SelectGDI.h"
#include "CCore.h"
#include "CObject.h"

CBossHpBarUI::CBossHpBarUI(int _iMaxHp)
	: m_iCurrHp(_iMaxHp)
	, m_iMaxHp(_iMaxHp)
{
}

CBossHpBarUI::~CBossHpBarUI()
{
}

void CBossHpBarUI::SetCurrHp(int _iCurrHp)
{
	if (_iCurrHp < 0)
		_iCurrHp = 0;
		
	m_iCurrHp = _iCurrHp;
}

void CBossHpBarUI::Render(HDC _dc)
{
	Vector2 vResolution = CCore::GetInst()->GetResolution();
	int posY = 70;
	int width = 300;
	int height = 30;
	int startPosX = ((vResolution.x / 2.f) - (width / 2.f));
	int endPosX = ((vResolution.x / 2.f) + (width / 2.f));

	SelectGDI whitePen(_dc, PEN_TYPE::WHITE);
	SelectGDI whiteBrush(_dc, BRUSH_TYPE::WHITE);
	Rectangle(_dc, startPosX, posY, endPosX, posY + height);

	SelectGDI redBrush(_dc, BRUSH_TYPE::RED);
	Rectangle(_dc, startPosX, posY
		, startPosX + (int)((float)width * ((float)m_iCurrHp / (float)m_iMaxHp))
		, posY + height);

	SetTextAlign(_dc, TA_CENTER);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(0, 0, 0));
	SelectGDI font(_dc, L"±¼¸²", 25);
	TextOut(_dc, vResolution.x / 2.f, posY + 2, L"BOSS", 4);

	if (m_iCurrHp == 0)
		DeleteObject(this);
}
