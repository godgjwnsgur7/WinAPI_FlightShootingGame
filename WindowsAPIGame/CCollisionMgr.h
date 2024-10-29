#pragma once

class CCollider;

union COLLIDER_ID
{
	struct
	{
		UINT LeftId;
		UINT RightId;
	};
	LONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	map<LONGLONG, bool> mapColInfo;
	UINT				arrCheck[(int)GROUP_TYPE::END];

public:
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};
