#include "pch.h"
#include "CScoreTextUI.h"

#include "CObject.h"
#include "SelectGDI.h"

CScoreTextUI::CScoreTextUI()
	: m_iScore(0)
{
}

CScoreTextUI::~CScoreTextUI()
{

}

wstring GetString(int number)
{
	string str = std::to_string(number);
	wstring answer = L"";
	for (int i = 0; i < str.size(); i++)
	{
		answer += str[i];

		int index = str.size() - i - 1;
		if (index != 0 && index % 3 == 0)
			answer += ',';
	}
	return answer;
}

void CScoreTextUI::Render(HDC _dc)
{
	SetTextAlign(_dc, TA_CENTER);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	SelectGDI font(_dc, L"±Ã¼­", 30);

	wstring str = GetString(m_iScore);
	TextOut(_dc, m_vPos.x, m_vPos.y, str.c_str(), str.size());
}