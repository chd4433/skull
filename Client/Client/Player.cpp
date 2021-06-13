#include "framework.h"
#include "Player.h"
#include "Throw.h"
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
		// 해당 상태에서 해야되는거

		// (임시) 발 아래에 타일이 없으면 낙하
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
		// 나중에 타일에 맞춰서 수정해야댐!

		// 이동
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			if (!m_bLeft)	m_bLeft = true;
			ChangeState(RUN);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
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

		// 공격
		if (m_pKeyMgr->KeyDown(KEY_ATTACK))
			ChangeState(ATTACK);

		// 하단 점프
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

		// 캐릭터 교체
		if (m_bChangeCharacter)
		{
			if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
				if (m_bCharacter1)	m_bCharacter1 = false;
				else				m_bCharacter1 = true;
				m_tInfo.fY--;
			}
		}

		break;
	case CPlayer::RUN:
		// 해당 상태에서 해야되는거
		cout << "x:" << m_tInfo.fX << ", y:" << m_tInfo.fY << endl;//
		// 이동
		if (m_bLeft) {
			m_tInfo.fX -= 5;
			if (m_tRect.left + iScrollX <= 800 - 500)//윈도우 - 사진크기 사진 왼쪽 기준  
				CScrollManager::Set_ScrollX(5);
		}
		else {
			m_tInfo.fX += 5;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-5);
		}
		// (임시) 옆에 타일로 막혀있으면 이동불가
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
		// 나중에 타일에 맞춰서 수정해야댐!

		// (임시) 발 아래에 타일이 없으면 낙하
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

		// 공격
		if (m_pKeyMgr->KeyDown(KEY_ATTACK))
			ChangeState(ATTACK);

		// 하단 점프
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
		// 캐릭터 교체
		if (m_bChangeCharacter)
		{
			if (m_pKeyMgr->KeyDown(KEY_CHANGE)) {
				if (m_bCharacter1)	m_bCharacter1 = false;
				else				m_bCharacter1 = true;
				m_tInfo.fY--;
			}
		}
		break;
	case CPlayer::DASH:
		if (m_bCharacter1) {
			if (m_bLeft) {
				m_tInfo.fX -= 8;
				if (m_tRect.left + iScrollX <= 800 - 500)//윈도우 - 사진크기 사진 왼쪽 기준  
					CScrollManager::Set_ScrollX(8);
			}
			else {
				m_tInfo.fX += 8;
				if (m_tRect.left + iScrollX >= 301)
					CScrollManager::Set_ScrollX(-8);
			}
			m_fDashLen += 8;
			// (임시) 옆에 타일로 막혀있으면 이동불가
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if (m_tInfo.fX - 8 <= 0)	m_tInfo.fX += 8;
				if (m_tInfo.fX - 8 <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += 8;
				if (m_tInfo.fX + 8 >= 1600)	m_tInfo.fX -= 8;
				if (m_tInfo.fX + 8 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 8;
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX - 8 <= 0)	m_tInfo.fX += 8;
				if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 8;
				if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 8;
				if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 8;
				if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 8;
				if (m_tInfo.fX + 8 >= 2400)	m_tInfo.fX -= 8;
				break;
			}
			// 나중에 타일에 맞춰서 수정해야댐!
		}
		else {
			if (m_bLeft) {
				m_tInfo.fX -= 3;
				if (m_tRect.left + iScrollX <= 800 - 500)//윈도우 - 사진크기 사진 왼쪽 기준  
					CScrollManager::Set_ScrollX(3);
			}
			else {
				m_tInfo.fX += 4;
				if (m_tRect.left + iScrollX >= 301)
					CScrollManager::Set_ScrollX(-3);
			}
			m_fDashLen += 3;
			// (임시) 옆에 타일로 막혀있으면 이동불가
			switch (CurrScene) {
			case SCENE_TUTORIAL:
				if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
				if (m_tInfo.fX - 3 <= 305 && m_tInfo.fY > 370)	m_tInfo.fX += 3;
				if (m_tInfo.fX + 3 >= 1600)	m_tInfo.fX -= 3;
				if (m_tInfo.fX + 3 >= 1160 && m_tInfo.fY > 370)	m_tInfo.fX -= 3;
				break;
			case SCENE_STAGE1:
				if (m_tInfo.fX - 3 <= 0)	m_tInfo.fX += 3;
				if (m_tInfo.fX >= 400 && m_tInfo.fX <= 410 && m_tInfo.fY >= 385)	m_tInfo.fX -= 3;
				if (m_tInfo.fX >= 515 && m_tInfo.fX <= 525 && m_tInfo.fY >= 385)	m_tInfo.fX += 3;
				if (m_tInfo.fX >= 1035 && m_tInfo.fX <= 1045 && m_tInfo.fY >= 385)	m_tInfo.fX -= 3;
				if (m_tInfo.fX >= 1470 && m_tInfo.fX <= 1480 && m_tInfo.fY >= 385)	m_tInfo.fX += 3;
				if (m_tInfo.fX + 3 >= 2400)	m_tInfo.fX -= 3;
				break;
			}
			// 나중에 타일에 맞춰서 수정해야댐!
		}

		// 일정 거리 대쉬하면 대쉬 종료
		if (m_fDashLen >= 96) {
			if (m_bJump || m_bFall) ChangeState(FALL);
			else if (m_pKeyMgr->KeyPressing(KEY_LEFT)
				|| m_pKeyMgr->KeyPressing(KEY_RIGHT)) ChangeState(RUN);
			else ChangeState(IDLE);

			m_fDashLen = 0;
		}
		break;
	case CPlayer::JUMP:
		cout << "x:" << m_tInfo.fX << ", y:" << m_tInfo.fY << endl;//
		m_tInfo.fY -= 8.f;
		m_fJumpHeight += 8.f;
		CScrollManager::Set_ScrollY(8);

		// 일정 높이 점프하면 떨어짐
		if (m_fJumpHeight >= 144)	ChangeState(FALL);

		// 이단 점프
		if (!m_bDoubleJump && m_pKeyMgr->KeyDown(KEY_UP)) {
			m_tInfo.fY -= 8;
			m_fJumpHeight = 0;
			m_bDoubleJump = true;
		}

		// 점프 중 이동
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_bLeft = true;
			m_tInfo.fX -= 4;
			if (m_tRect.left + iScrollX <= 800 - 500)//윈도우 - 사진크기 사진 왼쪽 기준  
				CScrollManager::Set_ScrollX(4);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX += 4;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-4);
		}
		// (임시) 옆에 타일로 막혀있으면 이동불가
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
		// 나중에 타일에 맞춰서 수정해야댐!

		// 점프 중 대쉬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
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
				|| (m_tInfo.fX >= 1200 && m_tInfo.fY > 345)) {		// 임시 땅바닥 ( 맵 타일 만들어지면 각 타일의 y축으로 바꾸면될듯? )
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
			m_tInfo.fX -= 3;
			if (m_tRect.left + iScrollX <= 800 - 500)//윈도우 - 사진크기 사진 왼쪽 기준  
				CScrollManager::Set_ScrollX(3);
		}
		if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_bLeft = false;
			m_tInfo.fX += 3;
			if (m_tRect.left + iScrollX >= 301)
				CScrollManager::Set_ScrollX(-3);
		}
		// (임시) 옆에 타일로 막혀있으면 이동불가
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
		// 나중에 타일에 맞춰서 수정해야댐!

		// 낙하 중 대쉬
		if (m_bCharacter1 && !m_bDash && m_pKeyMgr->KeyDown(KEY_DASH)) {
			if (!m_bDash)	m_bDash = true;
			ChangeState(DASH);
		}

		// 공격
		if (m_pKeyMgr->KeyDown(KEY_ATTACK))
			ChangeState(ATTACK);
		break;
	case CPlayer::ATTACK:
		m_fAttackCount++;

		// 투척
		if (!m_bCharacter1 && m_fAttackCount == 6 * 5)	m_pObjMgr->Add(THROW, CThrow::Create(m_tInfo.fX, m_tInfo.fY, m_bLeft));

		if ((m_bCharacter1 && m_fAttackCount >= 4 * 5) || (!m_bCharacter1 && m_fAttackCount >= 8 * 5)) {
			if (m_bFall)	ChangeState(FALL);
			else				ChangeState(IDLE);
			m_fAttackCount = 0;
		}

		if (m_bFall) {
			m_tInfo.fY += 1.f + m_fGravityAccel;
			m_fGravityAccel += 0.35f;

			// 발판 아래로 떨어지는 것 방지
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

	if (true) // 이걸 그릴지 말지 결정하는 조건
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
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
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
				m_tInfo.fCX = 50.f;
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
		case CPlayer::ATTACK:
			if (m_bCharacter1)
			{
				m_tInfo.fCX = 50.f;
				m_tInfo.fCY = 43.f;
				if (!m_bLeft)	SetFrame(L"Test", 10.f, 5, 1, 0, 5);
				else			SetFrame(L"Test2", 10.f, 5, 1, 0, 5);
			}
			else
			{
				m_tInfo.fCX = 50.f;
				m_tInfo.fCY = 50.f;
				if (!m_bLeft)	SetFrame(L"Test3", 10.f, 8, 1, 0, 5);
				else			SetFrame(L"Test4", 10.f, 8, 1, 0, 5);
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
