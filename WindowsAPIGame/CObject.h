#pragma once

#include "global.h"
#include "CCamera.h"

class CCollider;
class CAnimator;
class CRigidBody;

class CObject
{
protected:
	wstring m_strName;
	Vector2 m_vPos;
	Vector2 m_vScale;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool m_bAlive;

public:
	virtual void SetPos(Vector2 _vPos) { m_vPos = _vPos; }
	virtual void SetScale(Vector2 _vScale) { m_vScale = _vScale; }
	virtual void SetAnimScaleSize(float _fScaleSize);
	
public:
	Vector2 GetPos() { return m_vPos; }
	Vector2 GetScale() { return m_vScale; }
	
	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	bool IsDead() { return !m_bAlive; }
	virtual void DestroyMine() {}

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

public:
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

protected:
	virtual void SetDead() { m_bAlive = false; }

public:
	virtual void Start() {}
	virtual void Update() = 0;
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void ComponentRender(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class CEventMgr;
};