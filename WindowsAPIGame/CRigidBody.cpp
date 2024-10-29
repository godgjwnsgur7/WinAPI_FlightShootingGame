#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vector2(200.f, 1000.f))
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::FinalUpdate()
{
	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		m_vForce.Normalize();
		float m_fAccel = fForce / m_fMass;
		m_vAccel = m_vForce * m_fAccel;
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;
	
	// 속도
	m_vVelocity += m_vAccel * fDT;

	// 마찰력에 의한 반대방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vector2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vector2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vector2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	Move();
	m_vForce = Vector2(0.f, 0.f);

	m_vAccel = Vector2(0.f, 0.f);
	m_vAccelA = Vector2(0.f, 0.f);

}

void CRigidBody::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		Vector2 vDir = m_vVelocity;
		vDir.Normalize();

		Vector2 vPos = m_pOwner->GetPos();
		vPos += vDir * fSpeed * fDT;
		m_pOwner->SetPos(vPos);
	}
}
