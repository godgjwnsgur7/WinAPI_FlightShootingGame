#pragma once

class CCollisionWall;
class CDestructionWall;

class CWallGroup
{
private:
	CCollisionWall* m_pLeftColWall;
	CCollisionWall* m_pRightColWall;
	CCollisionWall* m_pUpColWall;
	CCollisionWall* m_pDownColWall;

	CDestructionWall* m_pLeftDesWall;
	CDestructionWall* m_pRightDesWall;
	CDestructionWall* m_pUpDesWall;
	CDestructionWall* m_pDownDesWall;

public:
	CWallGroup();
	~CWallGroup();
};

