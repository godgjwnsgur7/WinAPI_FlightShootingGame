#pragma once

#define SINGLE(type) public:\
static type* GetInst()\
{\
	static type mgr;\
	return &mgr;\
}\
private:\
type();\
~type();

#define fDT CTimeMgr::GetInst()->GetfDeltaTime();
#define DT CTimeMgr::GetInst()->GetDeltaTimeS();

#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key, state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415925435f

#define TILE_SIZE 64

/// <summary>
/// ·»´õ¸µ ¼ø¼­°¡ µÊ
/// </summary>
enum class GROUP_TYPE
{
	DEFAULT = 0,
	TILE,
	GROUND,
	WALL,
	BOOM_EFFECT,
	EXPLOSION_EFFECT,
	PLAYER_SUBUNIT,
	ITEM,
	PROJ_PLAYER,
	PROJ_MONSTER,
	MONSTER,
	PLAYER,
	BOSSMONSTER,

	UI_OBJECT = 30,
	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	TITLE,
	RESULT,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	RED,
	WHITE,
	GRAY,

	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	HOLLOW,

	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END
};

enum class MONSTER_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,
};

enum class MONSTER_TYPE
{
	ENEMY_S = 0,
	ENEMY_M = 1,
	ENEMY_L = 2,
};

enum class ITEM_TYPE
{
	POWER = 0,
	BOOM = 1,
};
