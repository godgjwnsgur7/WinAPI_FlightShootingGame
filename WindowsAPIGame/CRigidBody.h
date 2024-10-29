#pragma once


class CRigidBody
{
private:
	CObject*	m_pOwner;

	Vector2		m_vForce;
	Vector2		m_vAccel;
	Vector2		m_vAccelA;		// 추가 가속도
	Vector2		m_vVelocity;
	Vector2		m_vMaxVelocity;

	float		m_fMass;
	float		m_fFricCoeff; // 마찰 계수

public:
	void FinalUpdate();
	// void Render(HDC _dc);

public:
	void AddForce(Vector2 _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }
	float GetSpeed() { return m_vVelocity.Length(); }
	Vector2 GetVelocity() { return m_vVelocity; }

	void SetVelocity(Vector2 _v) { m_vVelocity = _v; }
	void AddVelocity(Vector2 _v) { m_vVelocity += _v; }
	void SetMaxVelocity(Vector2 _v) { m_vMaxVelocity = _v; }
	void SetAccelAlpha(Vector2 _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

