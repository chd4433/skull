#include "framework.h"
#include "FrameMgr.h"

IMPLEMENT_SINGLETON(CFrameMgr)

CFrameMgr::CFrameMgr()
{
	// 하드웨어에 있는 고해상도 타이머 값을 얻어오는 함수.
	// 타이머 값은 Cpu의 Clock을 기반으로 한다.
	// 결국 타이머 값은 누적 진동수다.
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceCounter(&m_OldTime);

	// Cpu의 Clock의 초당 진동수(Hz)를 얻어오는 함수.
	QueryPerformanceFrequency(&m_CpuTick);

	QueryPerformanceCounter(&m_FrameCurTime);
	QueryPerformanceCounter(&m_FrameOldTime);
	QueryPerformanceFrequency(&m_FrameCpuTick);
}

CFrameMgr::~CFrameMgr()
{
	Release();
}

const float& CFrameMgr::GetDelta() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return m_fDeltaTime;
}

void CFrameMgr::UpdateTime()//한 프레임 시간
{
	QueryPerformanceCounter(&m_CurTime);

	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceFrequency(&m_CpuTick);
	}

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;

	m_OldTime.QuadPart = m_CurTime.QuadPart;
}

bool CFrameMgr::FrameLimit(float fLimit)//프레임제한
{
	QueryPerformanceCounter(&m_FrameCurTime);

	if (m_FrameCurTime.QuadPart - m_FrameOldTime.QuadPart > m_FrameCpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_FrameCurTime);
		QueryPerformanceCounter(&m_FrameOldTime);
		QueryPerformanceFrequency(&m_FrameCpuTick);
	}

	m_fTimeCount += float(m_FrameCurTime.QuadPart - m_FrameOldTime.QuadPart) / m_FrameCpuTick.QuadPart;
	m_FrameOldTime.QuadPart = m_FrameCurTime.QuadPart;

	if ((1.f / fLimit) <= m_fTimeCount)
	{
		m_fTimeCount = 0.f;
		return true;
	}

	return false;
}

void CFrameMgr::Release()
{
}
