#include "pch.h"
#include "func.h"

#include "CEventMgr.h"
#include "CObject.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	if (_pObj == nullptr || _pObj->IsDead())
		return;

	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	
	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}
			
		_pOutBuff[i++] = c;
	}
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	// 문자 길이 저장
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// 문자열 저장
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);
	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	_str = szBuff;
}

vector<string> Split(string input, char delimiter)
{
	using namespace std;

	vector<string> answer;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter))
	{
		answer.push_back(temp);
	}

	answer[answer.size() - 1].pop_back();

	return answer;
}

wstring GetFormatString(int number)
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

Vector2 GetDirVec(int _angle)
{
	_angle %= 360;
	Vector2 vec((float)cos(_angle * 3.141592 / 180), (float)sin(_angle * 3.141592 / 180));
	return vec;
}