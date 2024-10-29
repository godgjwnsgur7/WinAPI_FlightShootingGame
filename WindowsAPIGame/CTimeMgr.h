#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER llCurrCount; // 현재 카운트
	LARGE_INTEGER llPrevCount; // 현재 카운트
	LARGE_INTEGER llFrequency; // 초당 카운트

	double m_deltaTime; // 프레임 사이 시간
	double m_deltaAcc; // 누적 시간
	UINT m_iCallCount; // 함수 호출 횟수
	UINT m_iFPS; // 초당 호출 횟수

public:
	void Init();
	void Update();
	void Render();
	
public:
	double GetDeltaTime() { return m_deltaTime; }
	float GetfDeltaTime() { return (float)m_deltaTime; }
	UINT GetCurrFPS() { return m_iFPS; }
};

