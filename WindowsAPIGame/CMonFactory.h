#pragma once

class CMonster;

class CMonFactory
{
public:
	static CMonster* CreateMonster(MONSTER_TYPE _eType, Vector2 _vPos);

private:
	CMonFactory() {}
	~CMonFactory() {}
};

