#include "framework.h"
#include "Player.h"
#include "Energyball.h"
#include "PoisonFlask.h"
#include "Grave.h"

SCENE_ID CurrScene = SCENE_END;

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

VOID CPlayer::SetRectPlayer(float fCX, float fCY)
{
	if (m_eCurrState == CPlayer::DASH) {
		rectPlayer.left = m_tInfo.fX - fCX / 2;
		rectPlayer.right = m_tInfo.fX + fCX / 2;
		rectPlayer.top = m_tInfo.fY - fCY / 2;
		rectPlayer.bottom = m_tInfo.fY + fCY / 2;
	}
	else {
		rectPlayer.left = m_tInfo.fX - fCX / 2;
		rectPlayer.right = m_tInfo.fX + fCX / 2;
		rectPlayer.top = m_tInfo.fY - fCY / 2;
		rectPlayer.bottom = m_tInfo.fY + fCY / 2;
	}
}

HRESULT CPlayer::Initialize()
{
	CObj::Initialize();

	m_tInfo.fX = 50.f;
	m_tInfo.fY = 345.f;
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_bCharacter1 = true;
	m_bLeft = false;

	ChangeState(IDLE);

	return NOERROR;
}

INT CPlayer::Update(const float& fTimeDelta)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	if (m_pObjMgr->Get_SingleObjLst(GRAVE)==nullptr)
	{
		m_bChangeCharacter = TRUE;
	}
	else
	{
		m_bChangeCharacter = dynamic_cast<CGrave*>(m_pObjMgr->Get_SingleObjLst(GRAVE))->GetbGrave();
	}
	switch (m_eCurrState)
	{
	case CPlayer::IDLE:
		// �� �Ʒ��� Ÿ���� ������ ����
		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if (m_tInfo.fX > 305 && m_tInfo.fX < 1160 && m_tInfo.fY < 505)	ChangeState(FALL);
			break;
		case SCENE_STAGE1:
			if (m_tInfo.fX < 400 && m_tInfo.fY <= 500)	ChangeState(FALL);
			if (m_tInfo.fX > 400 && m_tInfo.fX <= 520 && m_tInfo.fY < 385)	ChangeState(FALL);
			if (m_tInfo.fX > 520 && m_tInfo.fX <= 650 && m_tInfo.fY < 500)	ChangeState(FALL);
			if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY < 340)	ChangeState(FALL);
			if (m_tInfo.fX > 1000 && m_tInfo.fX <= 1035 && m_tInfo.fY < 500)	ChangeState(FALL);
			if (m_tInfo.fX > 1035 && m_tInfo.fX <= 1480 && m_tInfo.fY < 385)	ChangeState(FALL);
			if (m_tInfo.fX > 1480 && m_tInfo.fX <= 1720 && m_tInfo.fY < 500) ChangeState(FALL);
			if (m_tInfo.fX > 1720 && m_tInfo.fY < 265) ChangeState(FALL);
			break;
		}

		// �̵�
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			if (!m_bLeft)	m_bLeft = true;
			ChangeState(RUN);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
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

		// ����
		if (m_bCharacter1) {
			if (m_pKeyMgr->KeyPressing(KEY_ATTACK))
				ChangeState(ATTACK);
		}
		else {
			if (m_pKeyMgr->KeyDown(KEY_ATTACK))
				ChangeState(ATTACK);
		}

		// ��ų
		if (m_pKeyMgr->KeyDown(KEY_SKILL))
			ChangeState(SKILL);

		// �ϴ� ����
		if (m_pKeyMgr->KeyDown(KEY_DOWN)) {
			cout << "Down  " << m_tInfo.fY << endl;
			switch (CurrScene) {
			case SCENE_STAGE1:
				if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY == 340) {
					m_tInfo.fY += 20;
					ChangeState(FALL);
				}
				if (m_tInfo.fX > 1720 && m_tInfo.fY == 265) {
					m_tInfo.fY += 20;
					ChangeState(FALL);
				}
				break;
			}
		}

		// ĳ���� ��ü
		if (m_bChangeCharacter)
		{
			if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
				if (m_bCharacter1)	m_bCharacter1 = false;
				else				m_bCharacter1 = true;

				ChangeState(CHANGE);
			}
		}

		break;
	case CPlayer::RUN:
		cout << "x:" << m_tInfo.fX << ", y:" << m_tInfo.fY << endl;//
		// �̵�
		if (m_bLeft) {
			m_tInfo.fX -= 5;
			if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
				CScrollManager::Set_ScrollX(5);
		}
		else {
			m_tInfo.fX += 5;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-5);
		}
		// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if (m_tInfo.fX - 5 <= 0)	m_tInfo.fX += 5;
			if (m_tInfo.fX - 5 <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += 5;
			if (m_tInfo.fX + 5 >= 1600)	m_tInfo.fX -= 5;
			if (m_tInfo.fX + 5 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 5;
			break;
		case SCENE_STAGE1:
			if (m_tInfo.fX - 5 <= 0)	m_tInfo.fX += 5;
			if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 5;
			if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 5;
			if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 5;
			if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 5;
			if (m_tInfo.fX + 5 >= 2400)	m_tInfo.fX -= 5;
			break;
		}

		// �� �Ʒ��� Ÿ���� ������ ����
		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if (m_tInfo.fX > 310 && m_tInfo.fX < 1160 && m_tInfo.fY < 505)	ChangeState(FALL);
			break;
		case SCENE_STAGE1:
			if (m_tInfo.fX < 400 && m_tInfo.fY < 500)	ChangeState(FALL);
			if (m_tInfo.fX > 400 && m_tInfo.fX <= 520 && m_tInfo.fY < 385)	ChangeState(FALL);
			if (m_tInfo.fX > 520 && m_tInfo.fX <= 650 && m_tInfo.fY < 500)	ChangeState(FALL);
			if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY < 340)	ChangeState(FALL);
			if (m_tInfo.fX > 1000 && m_tInfo.fX <= 1035 && m_tInfo.fY < 500)	ChangeState(FALL);
			if (m_tInfo.fX > 1035 && m_tInfo.fX <= 1480 && m_tInfo.fY < 385)	ChangeState(FALL);
			if (m_tInfo.fX > 1480 && m_tInfo.fX <= 1720 && m_tInfo.fY < 500) ChangeState(FALL);
			if (m_tInfo.fX > 1720 && m_tInfo.fY < 265) ChangeState(FALL);
			break;
		}

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

		// ����
		if (m_bCharacter1) {
			if (m_pKeyMgr->KeyPressing(KEY_ATTACK))
				ChangeState(ATTACK);
		}
		else {
			if (m_pKeyMgr->KeyDown(KEY_ATTACK))
				ChangeState(ATTACK);
		}

		// ��ų
		if (m_pKeyMgr->KeyDown(KEY_SKILL))
			ChangeState(SKILL);

		// �ϴ� ����
		if (m_pKeyMgr->KeyDown(KEY_DOWN)) {
			cout << "Down  " << m_tInfo.fY << endl;
			switch (CurrScene) {
			case SCENE_STAGE1:
				if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY == 340) {
					m_tInfo.fY += 20;
					ChangeState(FALL);
				}
				if (m_tInfo.fX > 1720 && m_tInfo.fY == 265) {
					m_tInfo.fY += 20;
					ChangeState(FALL);
				}
				break;
			}

		}
		// ĳ���� ��ü
		if (m_bChangeCharacter)
		{
			if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
				if (m_bCharacter1)	m_bCharacter1 = false;
				else				m_bCharacter1 = true;

				ChangeState(CHANGE);
			}
		}
		break;
	case CPlayer::CHANGE:
		m_fChangeCount++;
		if (m_fChangeCount >= 15) {
			m_fChangeCount = 0.f;
			if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
				m_bLeft = true;
				ChangeState(RUN);
			}
			else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
				m_bLeft = false;
				ChangeState(RUN);
			}
			else ChangeState(IDLE);
		}
		break;
	case CPlayer::DASH:
		if (m_bCharacter1) {
			if (m_bLeft) {
				m_tInfo.fX -= 10;
				if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
					CScrollManager::Set_ScrollX(10);
			}
			else {
				m_tInfo.fX += 10;
				if (m_tRect.left + iScrollX >= 301)
					CScrollManager::Set_ScrollX(-10);
			}
			m_fDashLen += 10;
			// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if (m_tInfo.fX - 10 <= 0)							m_tInfo.fX += 10;
				if (m_tInfo.fX - 10 <= 305 && m_tInfo.fY > 370)		m_tInfo.fX += 10;
				if (m_tInfo.fX + 10 >= 1600)						m_tInfo.fX -= 10;
				if (m_tInfo.fX + 10 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 10;
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX - 10 <= 0)											m_tInfo.fX += 10;
				if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 10;
				if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 10;
				if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 10;
				if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 10;
				if (m_tInfo.fX + 10 >= 2400)										m_tInfo.fX -= 10;
				break;
			}

			// ���� �Ÿ� �뽬�ϸ� �뽬 ����
			if (m_fDashLen >= 110) {
				if (m_bJump || m_bFall) ChangeState(FALL);
				else if (m_pKeyMgr->KeyPressing(KEY_LEFT)
					|| m_pKeyMgr->KeyPressing(KEY_RIGHT)) ChangeState(RUN);
				else ChangeState(IDLE);

				m_fDashLen = 0;
			}
		}
		else {
			// Alchemist�� ��� ��ǿ� ���� �̵��ϴ� �Ÿ��� �ٸ� (�ڿ������� ������ ���ؼ�����)
			if (m_fDashCount < 2 * 5)		m_fDashLen = 8.f;
			else							m_fDashLen = 3.f;

			if (m_bLeft) {
				m_tInfo.fX -= m_fDashLen;
				if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
					CScrollManager::Set_ScrollX(m_fDashLen);
			}
			else {
				m_tInfo.fX += m_fDashLen;
				if (m_tRect.left + iScrollX >= 301)
					CScrollManager::Set_ScrollX(-m_fDashLen);
			}
			m_fDashCount++;
			// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if (m_tInfo.fX - m_fDashLen <= 0)						m_tInfo.fX += m_fDashLen;
				if (m_tInfo.fX - m_fDashLen <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += m_fDashLen;
				if (m_tInfo.fX + m_fDashLen >= 1600)						m_tInfo.fX -= m_fDashLen;
				if (m_tInfo.fX + m_fDashLen >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= m_fDashLen;
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX - m_fDashLen <= 0)									m_tInfo.fX += m_fDashLen;
				if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= m_fDashLen;
				if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += m_fDashLen;
				if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= m_fDashLen;
				if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += m_fDashLen;
				if (m_tInfo.fX + m_fDashLen >= 2400)								m_tInfo.fX = 2400 - m_fDashLen;
				break;
			}

			// ���� �Ÿ� �뽬�ϸ� �뽬 ����
			if (m_fDashCount == 8 * 5) {
				if (m_bJump || m_bFall) ChangeState(FALL);
				else if (m_pKeyMgr->KeyPressing(KEY_LEFT)
					|| m_pKeyMgr->KeyPressing(KEY_RIGHT)) ChangeState(RUN);
				else ChangeState(IDLE);

				m_fDashLen = m_fDashCount = 0.f;
			}
		}
		break;
	case CPlayer::JUMP:
		cout << "x:" << m_tInfo.fX << ", y:" << m_tInfo.fY << endl;//
		m_tInfo.fY -= 8.f;
		m_fJumpHeight += 8.f;
		CScrollManager::Set_ScrollY(8);

		// ���� ���� �����ϸ� ������
		if (m_fJumpHeight >= 144)	ChangeState(FALL);

		// �̴� ����
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = true;
		}

		// ���� �� �̵�
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX -= 4;
			if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
				CScrollManager::Set_ScrollX(4);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX += 4;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-4);
		}
		// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if (m_tInfo.fX - 4 <= 0)	m_tInfo.fX += 4;
			if (m_tInfo.fX - 4 <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += 4;
			if (m_tInfo.fX + 4 >= 1600)	m_tInfo.fX -= 4;
			if (m_tInfo.fX + 4 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 4;
			break;
		case SCENE_STAGE1:
			if (m_tInfo.fX - 4 <= 0)	m_tInfo.fX += 4;
			if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 4;
			if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 4;
			if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 4;
			if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 4;
			if (m_tInfo.fX + 4 >= 2400)	m_tInfo.fX -= 4;
			break;
		}

		// ���� �� �뽬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// ���� �� ��ų
		if (m_bCharacter1) {
			if (!m_bUsedSkill1 && m_pKeyMgr->KeyDown(KEY_SKILL)) {
				m_bUsedSkill1 = true;
				ChangeState(SKILL);
			}
		}

		break;
	case CPlayer::FALL:
		m_tInfo.fY += 1.f + m_fGravityAccel * m_fGravityAccel;
		//m_fGravityAccel += 0.35f;
		m_fGravityAccel += 0.13f;
		CScrollManager::Set_ScrollY(-(1.f + m_fGravityAccel * m_fGravityAccel));

		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if ((m_tInfo.fX <= 305 && m_tInfo.fY >= 345)
				|| (m_tInfo.fX > 305 && m_tInfo.fX < 1160 && m_tInfo.fY >= 505)
				|| (m_tInfo.fX >= 1200 && m_tInfo.fY > 345)) {
				if (m_tInfo.fX <= 305)	m_tInfo.fY = 345;
				else if (m_tInfo.fX >= 1160) m_tInfo.fY = 345;
				else					m_tInfo.fY = 505;
				ChangeState(IDLE);
			}
			break;
		case SCENE_STAGE1:
			if (m_tInfo.fX <= 400 && m_tInfo.fY >= 505)	{
				m_tInfo.fY = 505;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 400 && m_tInfo.fX < 530 && m_tInfo.fY >= 385){
				m_tInfo.fY = 385;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 520 && m_tInfo.fX <= 1035 && m_tInfo.fY >= 505) {
				m_tInfo.fY = 505;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY >= 340 && m_tInfo.fY <= 350) {
				m_tInfo.fY = 340;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 1035 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385) {
				m_tInfo.fY = 385;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 1480 && m_tInfo.fY >= 505) {
				m_tInfo.fY = 505;
				ChangeState(IDLE);
			}
			if (m_tInfo.fX > 1720 && m_tInfo.fY >= 265 && m_tInfo.fY <= 275) {
				m_tInfo.fY = 265;
				ChangeState(IDLE);
			}
				
			break;
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
			m_tInfo.fX -= 3;
			if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
				CScrollManager::Set_ScrollX(3);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX += 3;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-3);
		}
		// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
		switch (CurrScene) {
		case SCENE_TUTORIAL:
			if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
			if (m_tInfo.fX - 3 <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += 3;
			if (m_tInfo.fX + 3 >= 1600)	m_tInfo.fX -= 3;
			if (m_tInfo.fX + 3 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 3;
		case SCENE_STAGE1:
			if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
			if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 3;
			if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 3;
			if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 3;
			if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 3;
			if (m_tInfo.fX + 3 >= 2400)	m_tInfo.fX -= 3;
			break;
		}

		// ���� �� �뽬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// ����
		if (m_bCharacter1) {
			if (m_pKeyMgr->KeyPressing(KEY_ATTACK))
				ChangeState(ATTACK);
		}
		else {
			if (m_pKeyMgr->KeyDown(KEY_ATTACK))
				ChangeState(ATTACK);
		}

		// ���� �� ��ų
		if (m_bCharacter1) {
			if (!m_bUsedSkill1 && m_pKeyMgr->KeyDown(KEY_SKILL)) {
				m_bUsedSkill1 = true;
				ChangeState(SKILL);
			}
		}
		break;
	case CPlayer::ATTACK:
		m_fAttackCount++;

		if (m_bCharacter1) {
			switch (m_iSwordAttackMotion)
			{
			case 0:
				if (m_fAttackCount >= 5 * 3) {
					if (m_bFall)	ChangeState(FALL);
					else			ChangeState(IDLE);
					m_fAttackCount = 0;
					m_iSwordAttackMotion++;
				}
				break;
			case 1:
				if (m_fAttackCount >= 4 * 3) {
					if (m_bFall)	ChangeState(FALL);
					else			ChangeState(IDLE);
					m_fAttackCount = 0;
					m_iSwordAttackMotion++;
				}
				break;
			case 2:
				if (m_fAttackCount >= 6 * 3) {
					if (m_bFall)	ChangeState(FALL);
					else			ChangeState(IDLE);
					m_fAttackCount = 0;
					m_iSwordAttackMotion = 0;
				}
			}
			// �뽬 ���ĵ��
			if (!m_bDash) {
				if (m_pKeyMgr->KeyDown(KEY_DASH)) {
					if (m_pKeyMgr->KeyPressing(KEY_LEFT))		m_bLeft = true;
					else if (m_pKeyMgr->KeyPressing(KEY_RIGHT))	m_bLeft = false;
					m_bDash = true;
					m_fAttackCount = 0;
					m_iSwordAttackMotion = 0;
					ChangeState(DASH);
				}
			}
			// ���� ���ĵ��
			if (!m_bJump && !m_bFall) {
				if (m_pKeyMgr->KeyDown(KEY_UP)) {
					if (m_pKeyMgr->KeyPressing(KEY_LEFT))		m_bLeft = true;
					else if (m_pKeyMgr->KeyPressing(KEY_RIGHT))	m_bLeft = false;
					m_bJump = true;
					m_fAttackCount = 0;
					m_iSwordAttackMotion = 0;
					ChangeState(JUMP);
				}
			}
		}
		else {
			// ��ô
			if (m_fAttackCount <= 1) {
				if (m_bLeft)	m_pObjMgr->Add(PLAYER_ATT, CEnergyball::Create(m_tInfo.fX - 10, m_tInfo.fY - 10, m_bLeft));
				else			m_pObjMgr->Add(PLAYER_ATT, CEnergyball::Create(m_tInfo.fX + 10, m_tInfo.fY - 10, m_bLeft));
			}

			// ���� ����
			if (m_fAttackCount >= 5) {		// ��Ÿ��
				if (m_bFall)	ChangeState(FALL);
				else			ChangeState(IDLE);
				m_fAttackCount = 0;
			}
		}

		if (m_bFall) {
			m_tInfo.fY += 1.f + m_fGravityAccel;
			m_fGravityAccel += 0.35f;

			// ���� �Ʒ��� �������� �� ����
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if ((m_tInfo.fX <= 305 && m_tInfo.fY >= 345)
					|| (m_tInfo.fX > 305 && m_tInfo.fX < 1155 && m_tInfo.fY >= 505)
					|| (m_tInfo.fX >= 1155 && m_tInfo.fY > 345)) {
					if (m_tInfo.fX <= 305)	m_tInfo.fY = 345;
					else if (m_tInfo.fX >= 1155) m_tInfo.fY = 345;
					else					m_tInfo.fY = 505;
				}
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX <= 400 && m_tInfo.fY >= 505) {
					m_tInfo.fY = 505;
				}
				if (m_tInfo.fX > 400 && m_tInfo.fX < 530 && m_tInfo.fY >= 385) {
					m_tInfo.fY = 385;
				}
				if (m_tInfo.fX > 520 && m_tInfo.fX <= 1035 && m_tInfo.fY >= 505) {
					m_tInfo.fY = 505;
				}
				if (m_tInfo.fX > 650 && m_tInfo.fX <= 1000 && m_tInfo.fY >= 340 && m_tInfo.fY <= 350) {
					m_tInfo.fY = 339;
				}
				if (m_tInfo.fX > 1035 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385) {
					m_tInfo.fY = 385;
				}
				if (m_tInfo.fX > 1480 && m_tInfo.fY >= 505) {
					m_tInfo.fY = 505;
				}
				if (m_tInfo.fX > 1720 && m_tInfo.fY >= 265 && m_tInfo.fY <= 275) {
					m_tInfo.fY = 264;
				}

				break;
			}
		}
		break;
	case CPlayer::SKILL:
		if (m_bCharacter1) {
			if (m_fSkillDelay > 2 * 5) {	// Swordman�� skill1�� ���2 ������ ���ڸ����� �⸦ ��Ҵٰ� 3���� ���ư�.
				if (m_bLeft) {
					m_tInfo.fX -= 15;
					if (m_tRect.left + iScrollX <= 800 - 500)//������ - ����ũ�� ���� ���� ����  
						CScrollManager::Set_ScrollX(15);
				}
				else {
					m_tInfo.fX += 15;
					if (m_tRect.left + iScrollX >= 301)
						CScrollManager::Set_ScrollX(-15);
				}
				m_fDashLen += 15;
			}
			m_fSkillDelay++;
			// ���� Ÿ�Ϸ� ���������� �̵��Ұ�
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if (m_tInfo.fX - 15 <= 0)							m_tInfo.fX += 15;
				if (m_tInfo.fX - 15 <= 305 && m_tInfo.fY > 370)		m_tInfo.fX += 15;
				if (m_tInfo.fX + 15 >= 1600)						m_tInfo.fX -= 15;
				if (m_tInfo.fX + 15 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 15;
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX - 15 <= 0)											m_tInfo.fX += 15;
				if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 15;
				if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 15;
				if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 15;
				if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 15;
				if (m_tInfo.fX + 15 >= 2400)										m_tInfo.fX -= 15;
				break;
			}

			// ���� �Ÿ� �뽬�ϸ� �뽬 ����
			if (m_fDashLen >= 180) {
				if (m_bJump || m_bFall) ChangeState(FALL);
				else if (m_pKeyMgr->KeyPressing(KEY_LEFT)
					|| m_pKeyMgr->KeyPressing(KEY_RIGHT)) ChangeState(RUN);
				else ChangeState(IDLE);

				m_fDashLen = 0.f;
				m_fSkillDelay = 0.f;
			}
		}
		else
		{
			m_fAttackCount++;

			// ��ô
			if (m_fAttackCount == 6 * 5)	m_pObjMgr->Add(PLAYER_ATT, CPoisonFlask::Create(m_tInfo.fX, m_tInfo.fY, m_bLeft));

			if (m_fAttackCount >= 8 * 5) {
				ChangeState(IDLE);
				m_fAttackCount = 0;
			}
		}
		break;
	default:
		break;
	}
	/*
	if (m_pKeyMgr->KeyPressing(KEY_UP))
	{
		CScrollManager::Set_ScrollY(5);
	}
	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
	{
		CScrollManager::Set_ScrollY(-5);
	}
	*/

	CScrollManager::ScrollLock(CurrScene);
	//int iScrollX = CScrollManager::Get_ScrollX();
	//if (iScrollX == 0)
	//{
	//	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	//	{
	//		m_tInfo.fX -= 5;
	//	}
	//	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	//	{
	//		m_tInfo.fX += 5;
	//	}
	//}
	//if(iScrollX)
	FrameMove(fTimeDelta);

	if (true) // �̰� �׸��� ���� �����ϴ� ����
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CPlayer::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// ����� �׸��� ���� ��ǥ. 
		m_tInfo.fCX, m_tInfo.fCY,//�׸��� ��ü ���μ��� ũ�� 
		RGB(255, 0, 255));
}

HRESULT CPlayer::ChangeState(STATE eState)
{
	m_eCurrState = eState;
	cout << (int)m_eCurrState << endl;
	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CPlayer::IDLE:
			if (m_bJump)		m_bJump = false;
			if (m_bDoubleJump)	m_bDoubleJump = false;
			if (m_bFall)		m_bFall = false;
			if (m_bDash)		m_bDash = false;
			if (m_bUsedSkill1)	m_bUsedSkill1 = false;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)		SetFrame(L"S_IdleR", 10.f, 4, 1, 0, 0);
				else				SetFrame(L"S_IdleL", 10.f, 4, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 30.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_IdleR", 10.f, 6, 1, 0, 0);
				else			SetFrame(L"A_IdleL", 10.f, 6, 1, 0, 0);
			}
			break;
		case CPlayer::RUN:
			if (m_bDash)		m_bDash = false;
			if (m_bUsedSkill1)	m_bUsedSkill1 = false;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"S_RunR", 10.f, 8, 1, 0, 0);
				else			SetFrame(L"S_RunL", 10.f, 8, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_RunR", 10.f, 6, 1, 0, 0);
				else			SetFrame(L"A_RunL", 10.f, 6, 1, 0, 0);
			}
			break;
		case CPlayer::CHANGE:
			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 60.f;
				if (!m_bLeft)	SetFrame(L"S_SwitchR", 10.f, 1, 1, 0, 0);
				else			SetFrame(L"S_SwitchL", 10.f, 1, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_SwitchR", 10.f, 3, 1, 0, 0);
				else			SetFrame(L"A_SwitchL", 10.f, 3, 1, 0, 0);
			}
			break;
		case CPlayer::DASH:
			if (m_bCharacter1)
			{
				m_tInfo.fCX = 50.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)		SetFrame(L"S_DashR", 10.f, 4, 1, 0, 0);
				else				SetFrame(L"S_DashL", 10.f, 4, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_DashR", 10.f, 7, 1, 0, 0);
				else			SetFrame(L"A_DashL", 10.f, 7, 1, 0, 0);
			}
			break;
		case CPlayer::JUMP:
			if (!m_bJump)	m_bJump = true;
			m_fJumpHeight = 0.f;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"S_JumpR", 10.f, 1, 1, 0, 0);
				else			SetFrame(L"S_JumpL", 10.f, 1, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_JumpR", 10.f, 1, 1, 0, 0);
				else			SetFrame(L"A_JumpL", 10.f, 1, 1, 0, 0);
			}
			break;
		case CPlayer::FALL:
			m_fGravityAccel = 0;	// �߷°��ӵ� �ʱ�ȭ
			if (!m_bFall)	m_bJump = false, m_bFall = true;

			if (m_bCharacter1)
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)	SetFrame(L"S_FallR", 10.f, 2, 1, 0, 0);
				else			SetFrame(L"S_FallL", 10.f, 2, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 40.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_FallR", 10.f, 2, 1, 0, 0);
				else			SetFrame(L"A_FallL", 10.f, 2, 1, 0, 0);
			}
			break;
		case CPlayer::ATTACK:
			if (m_bCharacter1)
			{
				switch (m_iSwordAttackMotion)
				{
				case 0:
					m_tInfo.fCX = 50.f;
					m_tInfo.fCY = 50.f;
					if (!m_bLeft)	SetFrame(L"S_Attack1R", 15.f, 5, 1, 0, 0);
					else			SetFrame(L"S_Attack1L", 15.f, 5, 1, 0, 0);
					break;
				case 1:
					m_tInfo.fCX = 60.f;
					m_tInfo.fCY = 40.f;
					if (!m_bLeft)	SetFrame(L"S_Attack2R", 15.f, 4, 1, 0, 0);
					else			SetFrame(L"S_Attack2L", 15.f, 4, 1, 0, 0);
					break;
				case 2:
					m_tInfo.fCX = 60.f;
					m_tInfo.fCY = 40.f;
					if (!m_bLeft)	SetFrame(L"S_Attack3R", 15.f, 6, 1, 0, 0);
					else			SetFrame(L"S_Attack3L", 15.f, 6, 1, 0, 0);
					break;
				}
			}
			else
			{
				m_tInfo.fCX = 30.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_IdleR", 10.f, 6, 1, 0, 0);
				else			SetFrame(L"A_IdleL", 10.f, 6, 1, 0, 0);
			}
			break;
		case CPlayer::SKILL:
			if (m_bCharacter1)
			{
				m_tInfo.fCX = 60.f;
				m_tInfo.fCY = 40.f;
				if (!m_bLeft)		SetFrame(L"S_SkillR", 10.f, 6, 1, 0, 0);
				else				SetFrame(L"S_SkillL", 10.f, 6, 1, 0, 0);
			}
			else
			{
				m_tInfo.fCX = 50.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"A_SkillR", 10.f, 8, 1, 0, 0);
				else			SetFrame(L"A_SkillL", 10.f, 8, 1, 0, 0);
			}
			break;
		default:
			break;
		}

		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

VOID CPlayer::Update_Collision()
{
	switch (CurrScene)
	{
	case SCENE_LOGO:
		break;
	case SCENE_TUTORIAL:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map1Collision.txt");
		break;
	case SCENE_STAGE1:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map2Collision.txt");
		break;
	case SCENE_STAGE2:
		m_pCollisionMgr->LoadCollisionFromPath(L"../Binary/Map3Collision.txt");
		break;
	case SCENE_GAMEOVER:
		break;
	case SCENE_END:
		break;
	default:
		break;
	}

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
