#include "framework.h"
#include "Player.h"

SCENE_ID CurrScene = SCENE_END;

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{
	CObj::Initialize();

	m_tInfo.fX = 180.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_bCharacter1 = true;
	m_bLeft = false;

	ChangeState(IDLE);

	return NOERROR;
}

INT CPlayer::Update(const float& fTimeDelta)
{
	switch (m_eCurrState)
	{
	case CPlayer::IDLE:
		// 해당 상태에서 해야되는거

		// (임시) 발 아래에 타일이 없으면 낙하
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505)	ChangeState(FALL);		// 나중에 타일에 맞춰서 수정해야댐!

		// 이동
		if (m_pKeyMgr->KeyDown(KEY_LEFT)) {
			if (!m_bLeft)	m_bLeft = true;
			ChangeState(RUN);
		}
		if (m_pKeyMgr->KeyDown(KEY_RIGHT)) {
			if (m_bLeft)	m_bLeft = false;
			ChangeState(RUN);
		}

		// 대쉬
		if (!m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// 점프
		if (m_pKeyMgr->KeyDown(KEY_UP))
			ChangeState(JUMP);

		// 캐릭터 교체
		if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
			if (m_bCharacter1)	m_bCharacter1 = false;
			else				m_bCharacter1 = true;
			m_tInfo.fY--;
		}
		break;
	case CPlayer::RUN:
		// 해당 상태에서 해야되는거

		// 이동
		if (m_bLeft)	m_tInfo.fX -= 2;
		else			m_tInfo.fX += 2;
		// (임시) 옆에 타일로 막혀있으면 이동불가
		if (m_tInfo.fX - 2 <= 0)	m_tInfo.fX += 2;
		if (m_tInfo.fX - 2 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 2;
		// 나중에 타일에 맞춰서 수정해야댐!

		// (임시) 발 아래에 타일이 없으면 낙하
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505)	ChangeState(FALL);
		// 나중에 타일에 맞춰서 수정해야댐!

		// 멈춤
		if (!m_bLeft && m_pKeyMgr->KeyUp(KEY_RIGHT))
			ChangeState(IDLE);
		if (m_bLeft && m_pKeyMgr->KeyUp(KEY_LEFT))
			ChangeState(IDLE);

		// 대쉬
		if (!m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// 점프
		if (m_pKeyMgr->KeyDown(KEY_UP))
			ChangeState(JUMP);

		// 캐릭터 교체
		if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
			if (m_bCharacter1)	m_bCharacter1 = false;
			else				m_bCharacter1 = true;
			m_tInfo.fY--;
		}
		break;
	case CPlayer::DASH:
		if (m_bCharacter1) {
			if (m_bLeft)	m_tInfo.fX -= 8;
			else			m_tInfo.fX += 8;
			m_fDashLen += 8;
			// (임시) 옆에 타일로 막혀있으면 이동불가
			if (m_tInfo.fX - 8 <= 0)	m_tInfo.fX += 8;
			if (m_tInfo.fX - 8 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 8;
			// 나중에 타일에 맞춰서 수정해야댐!
		}
		else {
			if (m_bLeft)	m_tInfo.fX -= 3;
			else			m_tInfo.fX += 3;
			m_fDashLen += 3;
			// (임시) 옆에 타일로 막혀있으면 이동불가
			if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
			if (m_tInfo.fX - 3 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 3;
			// 나중에 타일에 맞춰서 수정해야댐!
		}

		// (임시) 발 아래에 타일이 없으면 낙하
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505 && !m_bDash )	ChangeState(FALL);
		// 나중에 타일에 맞춰서 수정해야댐!

		// 일정 거리 대쉬하면 대쉬 종료
		if (m_fDashLen >= 96) {
			if (m_bJump || m_bFall) ChangeState(FALL);
			else if (m_pKeyMgr->KeyPressing(KEY_LEFT)
				|| m_pKeyMgr->KeyPressing(KEY_RIGHT)) ChangeState(RUN);
			else ChangeState(IDLE);

			m_fDashLen = 0;
		}
		break;
	case CPlayer::JUMP://test
		m_tInfo.fY -= 8.f;
		m_fJumpHeight += 8.f;

		// 일정 높이 점프하면 떨어짐
		if (m_fJumpHeight >= 120)	ChangeState(FALL);

		// 이단 점프
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = true;
		}

		// 점프 중 이동
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX--;
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX++;
		}
		// (임시) 옆에 타일로 막혀있으면 이동불가
		if (m_tInfo.fX - 1 <= 0)	m_tInfo.fX += 1;
		if (m_tInfo.fX - 1 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 1;
		// 나중에 타일에 맞춰서 수정해야댐!

		// 점프 중 대쉬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}
		break;
	case CPlayer::FALL://test
		m_tInfo.fY += 1.f + m_fGravityAccel;
		m_fGravityAccel += 0.35f;

		if ((m_tInfo.fX <= 135 && m_tInfo.fY >= 345)
			|| (m_tInfo.fX > 135 && m_tInfo.fY >= 505)) {		// 임시 땅바닥 ( 맵 타일 만들어지면 각 타일의 y축으로 바꾸면될듯? )
			if (m_tInfo.fX <= 135)	m_tInfo.fY = 345;
			else					m_tInfo.fY = 505;
			ChangeState(IDLE);
		}

		// 낙하 중 이단 점프
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			ChangeState(JUMP);
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = m_bJump = true;
		}
		
		// 낙하 중 이동
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX--;
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX++;
		}
		// (임시) 옆에 타일로 막혀있으면 이동불가
		if (m_tInfo.fX - 1 <= 0)	m_tInfo.fX += 1;
		if (m_tInfo.fX - 1 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 1;
		// 나중에 타일에 맞춰서 수정해야댐!

		// 낙하 중 대쉬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}
		break;
	default:
		break;
	}

	FrameMove(fTimeDelta);

	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CPlayer::Render(HDC hDC)
{
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left, m_tRect.top,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

HRESULT CPlayer::ChangeState(STATE eState)
{
	m_eCurrState = eState;

	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CPlayer::IDLE:
			// 처음 이 상태로 들어갈때 해줘야 하는것들 여기ㅓ ㅅ해
			if (m_bJump)		m_bJump = false;
			if (m_bDoubleJump)	m_bDoubleJump = false;
			if (m_bFall)		m_bFall = false;
			if (m_bDash)		m_bDash = false;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)		SetFrame(L"Test", 10.f, 4, 1, 0, 0);
				else				SetFrame(L"Test2", 10.f, 4, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 30.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 6, 1, 0, 0);
				else			SetFrame(L"Test4", 10.f, 6, 1, 0, 0);
			}
			break;
		case CPlayer::RUN:
			if (m_bDash)		m_bDash = false;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"Test", 10.f, 8, 1, 0, 1);
				else			SetFrame(L"Test2", 10.f, 8, 1, 0, 1);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 6, 1, 0, 1);
				else			SetFrame(L"Test4", 10.f, 6, 1, 0, 1);
			}
			break;
		case CPlayer::DASH:
			if (m_bCharacter1)
			{
				m_tInfo.fCX = 50.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)		SetFrame(L"Test", 10.f, 4, 1, 0, 2);
				else				SetFrame(L"Test2", 10.f, 4, 1, 0, 2);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 7, 1, 0, 2);
				else			SetFrame(L"Test4", 10.f, 7, 1, 0, 2);
			}
			break;
		case CPlayer::JUMP:
			if (!m_bJump)	m_bJump = true;
			m_fJumpHeight = 0.f;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"Test", 10.f, 1, 1, 0, 3);
				else			SetFrame(L"Test2", 10.f, 1, 1, 0, 3);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 1, 1, 0, 3);
				else			SetFrame(L"Test4", 10.f, 1, 1, 0, 3);
			}
			break;
		case CPlayer::FALL:
			m_fGravityAccel = 0;	// 중력가속도 초기화
			if (!m_bFall)	m_bJump = false, m_bFall = true;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"Test", 10.f, 2, 1, 0, 4);
				else			SetFrame(L"Test2", 10.f, 2, 1, 0, 4);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 2, 1, 0, 4);
				else			SetFrame(L"Test4", 10.f, 2, 1, 0, 4);
			}
			break;
		default:
			break;
		}

		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

void CPlayer::Release()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;




}
