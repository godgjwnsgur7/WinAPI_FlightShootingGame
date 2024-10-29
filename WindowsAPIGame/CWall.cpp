#include "pch.h"
#include "CWall.h"

#include "CCollider.h"

CWall::CWall()
{
	CreateCollider();
}

CWall::~CWall()
{
}

void CWall::SetColliderScale(Vector2 _vScale)
{
	GetCollider()->SetScale(_vScale);
}

void CWall::SetColliderOffSet(Vector2 _vOffset)
{
	GetCollider()->SetOffsetPos(_vOffset);
}

void CWall::Render(HDC _dc)
{
	ComponentRender(_dc);
}
