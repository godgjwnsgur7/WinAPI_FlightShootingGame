#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, //LEFT,
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,

	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU, //ALT,
	VK_CONTROL, //CTRL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN, //ENTER,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,

	//LAST,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}

}

void CKeyMgr::Update()
{
	// HWND hMainWnd = CCore::GetInst()->
	// ();
	HWND hWnd = GetFocus();

	if (nullptr != hWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (vecKey[i].isPrevPush)
				{
					vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					vecKey[i].eState = KEY_STATE::TAP;
				}

				vecKey[i].isPrevPush = true;
			}
			else
			{
				if (vecKey[i].isPrevPush)
				{
					vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					vecKey[i].eState = KEY_STATE::NONE;
				}

				vecKey[i].isPrevPush = false;
			}
		}

		// Mouse
		POINT ptPos = {};
		GetCursorPos(&ptPos);
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		vCurrMousePos = Vector2((float)ptPos.x, (float)ptPos.y);
	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			vecKey[i].isPrevPush = false;

			if (KEY_STATE::TAP == vecKey[i].eState || KEY_STATE::HOLD == vecKey[i].eState)
			{
				vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == vecKey[i].eState)
			{
				vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}
