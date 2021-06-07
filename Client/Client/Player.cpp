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
		// �ش� ���¿��� �ؾߵǴ°�

		// (�ӽ�) �� �Ʒ��� Ÿ���� ������ ����
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505)	ChangeState(FALL);		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// �̵�
		if (m_pKeyMgr->KeyDown(KEY_LEFT)) {
			if (!m_bLeft)	m_bLeft = true;
			ChangeState(RUN);
		}
		if (m_pKeyMgr->KeyDown(KEY_RIGHT)) {
			if (m_bLeft)	m_bLeft = false;
			ChangeState(RUN);
		}

		// �뽬
		if (!m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// ����
		if (m_pKeyMgr->KeyDown(KEY_UP))
			ChangeState(JUMP);

		// ĳ���� ��ü
		if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
			if (m_bCharacter1)	m_bCharacter1 = false;
			else				m_bCharacter1 = true;
			m_tInfo.fY--;
		}
		break;
	case CPlayer::RUN:
		// �ش� ���¿��� �ؾߵǴ°�

		// �̵�
		if (m_bLeft)	m_tInfo.fX -= 2;
		else			m_tInfo.fX += 2;
		// (�ӽ�) ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		if (m_tInfo.fX - 2 <= 0)	m_tInfo.fX += 2;
		if (m_tInfo.fX - 2 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 2;
		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// (�ӽ�) �� �Ʒ��� Ÿ���� ������ ����
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505)	ChangeState(FALL);
		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// ����
		if (!m_bLeft && m_pKeyMgr->KeyUp(KEY_RIGHT))
			ChangeState(IDLE);
		if (m_bLeft && m_pKeyMgr->KeyUp(KEY_LEFT))
			ChangeState(IDLE);

		// �뽬
		if (!m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// ����
		if (m_pKeyMgr->KeyDown(KEY_UP))
			ChangeState(JUMP);

		// ĳ���� ��ü
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
			// (�ӽ�) ���� Ÿ�Ϸ� ���������� �̵��Ұ�
			if (m_tInfo.fX - 8 <= 0)	m_tInfo.fX += 8;
			if (m_tInfo.fX - 8 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 8;
			// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!
		}
		else {
			if (m_bLeft)	m_tInfo.fX -= 3;
			else			m_tInfo.fX += 3;
			m_fDashLen += 3;
			// (�ӽ�) ���� Ÿ�Ϸ� ���������� �̵��Ұ�
			if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
			if (m_tInfo.fX - 3 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 3;
			// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!
		}

		// (�ӽ�) �� �Ʒ��� Ÿ���� ������ ����
		if (m_tInfo.fX > 135 && m_tInfo.fY < 505 && !m_bDash )	ChangeState(FALL);
		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// ���� �Ÿ� �뽬�ϸ� �뽬 ����
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

		// ���� ���� �����ϸ� ������
		if (m_fJumpHeight >= 120)	ChangeState(FALL);

		// �̴� ����
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = true;
		}

		// ���� �� �̵�
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX--;
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX++;
		}
		// (�ӽ�) ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		if (m_tInfo.fX - 1 <= 0)	m_tInfo.fX += 1;
		if (m_tInfo.fX - 1 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 1;
		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// ���� �� �뽬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}
		break;
	case CPlayer::FALL://test
		m_tInfo.fY += 1.f + m_fGravityAccel;
		m_fGravityAccel += 0.35f;

		if ((m_tInfo.fX <= 135 && m_tInfo.fY >= 345)
			|| (m_tInfo.fX > 135 && m_tInfo.fY >= 505)) {		// �ӽ� ���ٴ� ( �� Ÿ�� ��������� �� Ÿ���� y������ �ٲٸ�ɵ�? )
			if (m_tInfo.fX <= 135)	m_tInfo.fY = 345;
			else					m_tInfo.fY = 505;
			ChangeState(IDLE);
		}

		// ���� �� �̴� ����
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			ChangeState(JUMP);
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = m_bJump = true;
		}
		
		// ���� �� �̵�
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX--;
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX++;
		}
		// (�ӽ�) ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		if (m_tInfo.fX - 1 <= 0)	m_tInfo.fX += 1;
		if (m_tInfo.fX - 1 <= 135 && m_tInfo.fY > 370)	m_tInfo.fX += 1;
		// ���߿� Ÿ�Ͽ� ���缭 �����ؾߴ�!

		// ���� �� �뽬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}
		break;
	default:
		break;
	}

	FrameMove(fTimeDelta);

	if (true) // �̰� �׸��� ���� �����ϴ� ����
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
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// ����� �׸��� ���� ��ǥ. 
		m_tInfo.fCX, m_tInfo.fCY,//�׸��� ��ü ���μ��� ũ�� 
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
			// ó�� �� ���·� ���� ����� �ϴ°͵� ����� ����
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
			m_fGravityAccel = 0;	// �߷°��ӵ� �ʱ�ȭ
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
