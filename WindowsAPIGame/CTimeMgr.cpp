#include "pch.h"
#include "CTimeMgr.h"

#include "CCore.h"

CTimeMgr::CTimeMgr() : llCurrCount{}, llPrevCount{}
, llFrequency{}, m_deltaTime(0.), m_deltaAcc(0.), m_iCallCount(0), m_iFPS(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Init()
{
	llPrevCount.QuadPart;
	llPrevCount.u;
	llPrevCount.u.LowPart;
	llPrevCount.u.HighPart;
	llPrevCount.LowPart;
	llPrevCount.HighPart;

	QueryPerformanceCounter(&llPrevCount);
	QueryPerformanceFrequency(&llFrequency);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&llCurrCount);
	m_deltaTime = (double)(llCurrCount.QuadPart - llPrevCount.QuadPart) / (double)(llFrequency.QuadPart);
	llPrevCount = llCurrCount;
}

void CTimeMgr::Render()
{
	++m_iCallCount;
	m_deltaAcc += m_deltaTime;

	if (m_deltaAcc >= 1.)
	{
		m_iFPS = m_iCallCount;
		m_deltaAcc = 0.;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_deltaTime);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
