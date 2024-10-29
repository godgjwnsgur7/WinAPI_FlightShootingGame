#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* m_pOwner; /// ������
	Vector2 m_vOffsetPos; // ����� ��ġ
	Vector2 m_vFinalPos; // �� �����Ӹ��� ��� (FinalUpdate) 
	Vector2 m_vScale;

	UINT	m_iID;
	int		m_iCol;

	bool	m_bActive;

public:
	void SetOffsetPos(Vector2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vector2 _vScale) { m_vScale = _vScale; }

	Vector2 GetOffsetPos() { return m_vOffsetPos; }
	Vector2 GetScale() { return m_vScale; }
	
	Vector2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete; // ���� �Ұ�

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

