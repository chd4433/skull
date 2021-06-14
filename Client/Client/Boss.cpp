#include "framework.h"
#include "Boss.h"
#include<random>

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
}

HRESULT CBoss::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 76.f;
	m_tInfo.fCY = 66.f;
	m_bRight = FALSE;
	m_bGetTick = FALSE;
	m_bMotionGetTick = FALSE;
	m_bAttackMotion = FALSE;
	m_bDead = FALSE;
	ChangeState(IDLE);

	iMonsterHp = 200;
	return NOERROR;
}

INT CBoss::Update(const float& fTimeDelta)
{
	CheckDash();
	CheckAttackA();
	switch (m_eCurrState)
	{
	case CBoss::IDLE:
		break;
	case CBoss::ATTACK1:
		break;
	case CBoss::ATTACK2:
		break;
	case CBoss::DASH:
		if (!m_bAttackMotion)
			m_tInfo.fX -= 5;
		else
			m_tInfo.fX += 5;
		break;
	case CBoss::HIT:
		break;
	case CBoss::DEAD:
		break;
	default:
		break;
	}
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CBoss::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CBoss* CBoss::Create(float fStartX, float fStartY)
{
	CBoss* pInstance = new CBoss;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

HRESULT CBoss::ChangeState(STATE eState)
{
	m_eCurrState = eState;

	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CBoss::IDLE:
			if (!m_bRight)
				SetFrame(L"Boss_IdleL", 10.f, 6, 1);
			else
				SetFrame(L"Boss_IdleL", 10.f, 6, 1);
			break;
		case CBoss::ATTACK1:
			if (!m_bAttackMotion)
				SetFrame(L"Boss_AttackL_A", 10.f, 9, 1);
			else
				SetFrame(L"Boss_AttackR_A", 10.f, 9, 1);
			SetInfo(115.f, 94.f);
			break;
		case CBoss::ATTACK2:
			if (!m_bAttackMotion)
				SetFrame(L"Boss_AttackL_B", 10.f, 4, 1);
			else
				SetFrame(L"Boss_AttackR_B", 10.f, 4, 1);
			SetInfo(139.f, 108.f);
			break;
		case CBoss::DASH:
			if (!m_bAttackMotion)
				SetFrame(L"Boss_DashL", 10.f, 3, 1);
			else
				SetFrame(L"Boss_DashR", 10.f, 3, 1);
			SetInfo(103.f, 56.f);
			break;
		case CBoss::HIT:
			break;
		case CBoss::DEAD:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

BOOL CBoss::CheckDash()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayerL = m_tRect;
	RECT CheckPlayerR = m_tRect;
	CheckPlayerL.left -= 150;//원래 870
	CheckPlayerR.right += 150;
	if (IntersectRect(&temp, &CheckPlayerL, &PlayerRect) && m_tFrame.fX == 0)
	{
		if (!m_bMotionGetTick)
		{
			AttackMotion_Time = GetTickCount();
			m_bMotionGetTick = !m_bMotionGetTick;
		}
		if (AttackMotion_Time + 1000 < GetTickCount())
		{
			m_bAttackMotion = FALSE;
			m_bRight = FALSE;
			ChangeState(DASH);
		}

	}
	if (IntersectRect(&temp, &CheckPlayerR, &PlayerRect) && m_tFrame.fX == 0)
	{
		if (!m_bMotionGetTick)
		{
			AttackMotion_Time = GetTickCount();
			m_bMotionGetTick = !m_bMotionGetTick;
		}
		if (AttackMotion_Time + 1000 < GetTickCount())
		{
			m_bAttackMotion = TRUE;
			m_bRight = TRUE;
			ChangeState(DASH);
		}

	}
	return 0;
}

BOOL CBoss::CheckAttackA()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayerL = m_tRect;
	RECT CheckPlayerR = m_tRect;
	CheckPlayerL.left -= 50, CheckPlayerL.right = m_tInfo.fX;
	CheckPlayerR.right += 50, CheckPlayerR.left = m_tInfo.fX;
	if (IntersectRect(&temp, &CheckPlayerL, &PlayerRect) && m_tFrame.fX == 0)
	{
		if (!m_bMotionGetTick)
		{
			AttackMotion_Time = GetTickCount();
			m_bMotionGetTick = !m_bMotionGetTick;
		}
		if (AttackMotion_Time + 1000 < GetTickCount())
		{
			m_bAttackMotion = FALSE;
			m_bRight = FALSE;
			if (RandAttack() == 1)
				ChangeState(ATTACK1);
			else
				ChangeState(ATTACK2);
		}

	}
	if (IntersectRect(&temp, &CheckPlayerR, &PlayerRect) && m_tFrame.fX == 0)
	{
		if (!m_bMotionGetTick)
		{
			AttackMotion_Time = GetTickCount();
			m_bMotionGetTick = !m_bMotionGetTick;
		}
		if (AttackMotion_Time + 1000 < GetTickCount())
		{
			m_bAttackMotion = TRUE;
			m_bRight = TRUE;
			if (RandAttack() == 1)
				ChangeState(ATTACK1);
			else
				ChangeState(ATTACK2);
		}

	}
	return 0;
}

int CBoss::RandAttack()
{
	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<int> uid(1, 2);
	int iRand = uid(dre);
	return iRand;
}

void CBoss::SetRect()
{
}

void CBoss::Release()
{
}

