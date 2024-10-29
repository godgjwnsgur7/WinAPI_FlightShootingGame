#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER llCurrCount; // ���� ī��Ʈ
	LARGE_INTEGER llPrevCount; // ���� ī��Ʈ
	LARGE_INTEGER llFrequency; // �ʴ� ī��Ʈ

	double m_deltaTime; // ������ ���� �ð�
	double m_deltaAcc; // ���� �ð�
	UINT m_iCallCount; // �Լ� ȣ�� Ƚ��
	UINT m_iFPS; // �ʴ� ȣ�� Ƚ��

public:
	void Init();
	void Update();
	void Render();
	
public:
	double GetDeltaTime() { return m_deltaTime; }
	float GetfDeltaTime() { return (float)m_deltaTime; }
	UINT GetCurrFPS() { return m_iFPS; }
};

