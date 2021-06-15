#include "framework.h"
#include "MovingTree.h"
#include "MovingTreeAttack.h"

CMovingTree::CMovingTree()
{
}

CMovingTree::~CMovingTree()
{
}

HRESULT CMovingTree::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 53.f;
	m_tInfo.fCY = 65.f;
	m_bRight = FALSE;
	m_bGetTick = FALSE;
	m_bMotionGetTick = FALSE;
	m_bAttackMotion = FALSE;
	m_bDead = FALSE;
	ChangeState(WALK);
	iAttDamageBool = 0;
	iMonsterHp = 300;
	return NOERROR;
}

INT CMovingTree::Update(const float& fTimeDelta)
{
	SetRect();
	CheckWalk();
	CheckAttack();
	Update_Collision();
	if (b_ChangeSceneDead)
	{
		ChangeState(HIT);
		iAttDamageBool = 1;
		if (m_tFrame.fX == 0)
			b_ChangeSceneDead = FALSE;
	}
	if (b_ChangeDeadCloseAtt)
	{
		ChangeState(HIT);
		iAttDamageBool = 2;
		if (m_tFrame.fX == 0)
			b_ChangeDeadCloseAtt = FALSE;
	}
	if (iMonsterHp <= 0)
	{
		ChangeState(DEAD);
	}
	switch (m_eCurrState)
	{
	case CMovingTree::ATTACK:
		if (m_tFrame.fX == 0)
			m_pObjMgr->Add(MON_CLOSEATT, CMovingTreeAttack::Create(m_tInfo.fX, m_tInfo.fY));
		break;
	case CMovingTree::WALK:
		if (!m_bRight)
		{
			for (auto pCollRect : m_pCollisionMgr->GetlistCollision())
			{
				RECT tTemp = {};
				RECT tDstRect = { pCollRect->left,pCollRect->top,pCollRect->right,pCollRect->bottom };
				if (IntersectRect(&tTemp, &rectMovingTree, &tDstRect))
				{
					float fDstX = (float)tDstRect.right - tDstRect.left;
					float fDstY = (float)tDstRect.bottom - tDstRect.top;

					float fMoveX = (float)tTemp.right - tTemp.left;
					float fMoveY = (float)tTemp.bottom - tTemp.top;
					if (fMoveX < fMoveY)
					{
						if (m_tInfo.fX < (tDstRect.right + tDstRect.left) / 2)
						{
							m_tInfo.fX -= fMoveX + 1;
							m_bRight = !m_bRight;
							SetFrame(L"MovingTree_WalkL", 10.f, 6, 1);
						}
						else
						{
							m_tInfo.fX += fMoveX + 1;
							m_bRight = !m_bRight;
							SetFrame(L"MovingTree_WalkR", 10.f, 6, 1);
						}
					}
				}
			}
			--m_tInfo.fX;
		}
		else
		{
			for (auto pCollRect : m_pCollisionMgr->GetlistCollision())
			{
				RECT tTemp = {};
				RECT tDstRect = { pCollRect->left,pCollRect->top,pCollRect->right,pCollRect->bottom };
				if (IntersectRect(&tTemp, &rectMovingTree, &tDstRect))
				{
					float fDstX = (float)tDstRect.right - tDstRect.left;
					float fDstY = (float)tDstRect.bottom - tDstRect.top;

					float fMoveX = (float)tTemp.right - tTemp.left;
					float fMoveY = (float)tTemp.bottom - tTemp.top;
					if (fMoveX < fMoveY)
					{
						if (m_tInfo.fX < (tDstRect.right + tDstRect.left) / 2)
						{
							m_tInfo.fX -= fMoveX + 1;
							m_bRight = !m_bRight;
							SetFrame(L"MovingTree_WalkL", 10.f, 6, 1);
						}
						else
						{
							m_tInfo.fX += fMoveX + 1;
							m_bRight = !m_bRight;
							SetFrame(L"MovingTree_WalkR", 10.f, 6, 1);
						}
					}
				}
			}
			++m_tInfo.fX;
		}
		break;
	case CMovingTree::HIT:
		if (!m_bRight)
			++m_tInfo.fX;
		else
			--m_tInfo.fX;
		if (m_tFrame.fX == 0)
		{
			if (iAttDamageBool == 1)
				iMonsterHp -= PLAYERATT;
			else if (iAttDamageBool == 2)
				iMonsterHp -= PLAYERATTCLOSE;
		}
		break;
	case CMovingTree::DEAD:
		if (m_tFrame.fX == 0 && m_bDead)
			return OBJ_DEAD;
		if (m_tFrame.fX == 0 && !m_bDead)
			m_bDead = !m_bDead;
		break;
	default:
		break;
	}
	m_pCollisionMgr->Release();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CMovingTree::Render(HDC hDC)
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

CMovingTree* CMovingTree::Create(float fStartX, float fStartY)
{
	CMovingTree* pInstance = new CMovingTree;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

HRESULT CMovingTree::ChangeState(STATE eState)
{
	m_eCurrState = eState;

	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CMovingTree::ATTACK:
			if (!m_bAttackMotion)
			{
				SetFrame(L"MovingTree_AttackL", 5.f, 4, 1);
				m_bRight = FALSE;
			}
			else
			{
				SetFrame(L"MovingTree_AttackR", 5.f, 4, 1);
				m_bRight = TRUE;
			}
			SetInfo(59.f, 64.f);
			break;
		case CMovingTree::WALK:
			if (!m_bRight)
				SetFrame(L"MovingTree_WalkL", 10.f, 6, 1);
			else
				SetFrame(L"MovingTree_WalkR", 10.f, 6, 1);
			m_tInfo.fCX = 53.f;
			m_tInfo.fCY = 65.f;
			break;
		case CMovingTree::HIT:
			if (!m_bRight)
				SetFrame(L"MovingTree_HitL", 10.f, 5, 1);
			else
				SetFrame(L"MovingTree_HitR", 10.f, 5, 1);
			SetInfo(56.f, 66.f);
			break;
		case CMovingTree::DEAD:
			if (!m_bRight)
				SetFrame(L"MovingTree_DeadL", 10.f, 1, 1);
			else
				SetFrame(L"MovingTree_DeadR", 10.f, 1, 1);
			SetInfo(76.f, 33.f);
			m_tInfo.fY += 20;
			break;
			break;
		default:
			break;
		}
		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

BOOL CMovingTree::CheckWalk()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayer = m_tRect;
	CheckPlayer.left -= 450, CheckPlayer.right += 500, CheckPlayer.top -= 520;
	if (IntersectRect(&temp, &CheckPlayer, &PlayerRect) && m_tFrame.fX == 0)
	{
		ChangeState(WALK);
	}
	return 0;
}

BOOL CMovingTree::CheckAttack()
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
			ChangeState(ATTACK);
			m_bAttackMotion = FALSE;
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
			ChangeState(ATTACK);
			m_bAttackMotion = TRUE;
		}

	}
	return 0;
}

void CMovingTree::SetRect()
{
	rectMovingTree.left = m_tInfo.fX - 18;
	rectMovingTree.right = m_tInfo.fX + 18;
	rectMovingTree.top = m_tRect.top;
	rectMovingTree.bottom = m_tRect.bottom;
}

void CMovingTree::Release()
{
}
