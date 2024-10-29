#pragma once

enum class KEY_STATE
{
	NONE,
	TAP, // 막 누름
	HOLD, // 누르고 있음
	AWAY, // 막 뗌
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LBTN,
	RBTN,

	LAST,
};

struct tKeyInfo
{
	KEY_STATE eState;
	bool isPrevPush;
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:
	vector<tKeyInfo>	vecKey;
	Vector2				vCurrMousePos;

public:
	void Init();
	void Update();

public:
	KEY_STATE GetKeyState(KEY _eKey) { return vecKey[(int)_eKey].eState; }
	Vector2 GetMousePos() { return vCurrMousePos; }
};

