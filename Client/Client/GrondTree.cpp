#include "framework.h"
#include "GrondTree.h"
#include "Player.h"
#include "GroundTreeAttack.h"

CGrondTree::CGrondTree():CObj()
{
}

CGrondTree::~CGrondTree()
{
	Release();
}

HRESULT CGrondTree::Initialize(float fStartX, float fStartY)
{
	m_bRight = false;
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 66.f;
	m_bGetTick = FALSE;
	m_bMotionGetTick = FALSE;
	m_bAttackMotion = FALSE;
	m_bDead = FALSE;
	ChangeState(IDLE);
	iAttDamageBool = 0;
	iMonsterHp = 200;
	return NOERROR;
}

INT CGrondTree::Update(const float& fTimeDelta)
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
	if (m_pKeyMgr->KeyDown(KEY_CHEAT))
		return OBJ_DEAD;
	switch (m_eCurrState)
	{
	case CGrondTree::IDLE:
		if (!m_bRight)
		//else
			break;
	case CGrondTree::WALK:
		if (!m_bRight)
		{
			for (auto pCollRect : m_pCollisionMgr->GetlistCollision())
			{
				RECT tTemp = {};
				RECT tDstRect = { pCollRect->left,pCollRect->top,pCollRect->right,pCollRect->bottom };
				if (IntersectRect(&tTemp, &rectGroundTree, &tDstRect))
				{
					float fDstX = (float)tDstRect.right - tDstRect.left;
					float fDstY = (float)tDstRect.bottom - tDstRect.top;

					float fMoveX = (float)tTemp.right - tTemp.left;
					float fMoveY = (float)tTemp.bottom - tTemp.top;
					if (fMoveX < fMoveY)
					{
						if (m_tInfo.fX < (tDstRect.right + tDstRect.left) / 2)
						{
							m_tInfo.fX -= fMoveX+1;
							m_bRight = !m_bRight;
							SetFrame(L"GroundTree_WalkL", 10.f, 6, 1);
						}
						else
						{
							m_tInfo.fX += fMoveX+1;
							m_bRight = !m_bRight;
							SetFrame(L"GroundTree_WalkR", 10.f, 6, 1);
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
				if (IntersectRect(&tTemp, &rectGroundTree, &tDstRect))
				{
					float fDstX = (float)tDstRect.right - tDstRect.left;
					float fDstY = (float)tDstRect.bottom - tDstRect.top;

					float fMoveX = (float)tTemp.right - tTemp.left;
					float fMoveY = (float)tTemp.bottom - tTemp.top;
					if (fMoveX < fMoveY)
					{
						if (m_tInfo.fX < (tDstRect.right + tDstRect.left) / 2)
						{
							m_tInfo.fX -= fMoveX+1;
							m_bRight = !m_bRight;
							SetFrame(L"GroundTree_WalkL", 10.f, 6, 1);
						}
						else
						{
							m_tInfo.fX += fMoveX+1;
							m_bRight = !m_bRight;
							SetFrame(L"GroundTree_WalkR", 10.f, 6, 1);
						}
					}
				}
			}
			++m_tInfo.fX;
		}
		break;
	case CGrondTree::ATTACK:
		if (!m_bGetTick)
		{
			Attack_Time = GetTickCount();
			m_bGetTick = !m_bGetTick;
		}
		if (Attack_Time + 1000 < GetTickCount()&& m_tFrame.fX > 6)
		{
			m_pObjMgr->Add(MON_ATT, CGroundTreeAttack::Create());
			m_bGetTick = !m_bGetTick;
		}
		break;
	case CGrondTree::HIT:
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
	case CGrondTree::DEAD:
		if(m_tFrame.fX == 0 && m_bDead)
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

VOID CGrondTree::Render(HDC hDC)
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

HRESULT CGrondTree::ChangeState(STATE eState)
{
	m_eCurrState = eState;

	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CGrondTree::IDLE:
			// 처음 이 상태로 들어갈때 해줘야 하는것들 여기ㅓ ㅅ해
			//m_tInfo.fCX = 197.f;
			//m_tInfo.fCY = 226.f;
			if (!m_bRight)
				SetFrame(L"GroundTree_IdleL", 10.f, 5, 1);
			else
				SetFrame(L"GroundTree_IdleR", 10.f, 5, 1);
			break;
		case CGrondTree::WALK:
			if (!m_bRight)
				SetFrame(L"GroundTree_WalkL", 10.f, 6, 1);
			else
				SetFrame(L"GroundTree_WalkR", 10.f, 6, 1);
			SetInfo(54.f, 65.f);
			break;
		case CGrondTree::ATTACK:
			if (!m_bAttackMotion)
			{
				SetFrame(L"GroundTree_AttackL", 5.f, 8, 1);
				m_bRight = FALSE;
			}
			else
			{
				SetFrame(L"GroundTree_AttackR", 5.f, 8, 1);
				m_bRight = TRUE;
			}
			
			SetInfo(82.f, 67.f);
			break;
		case CGrondTree::HIT:
			if (!m_bRight)
				SetFrame(L"GroundTree_HitL", 10.f, 2, 1);
			else
				SetFrame(L"GroundTree_HitR", 10.f, 2, 1);
			SetInfo(62.f, 66.f);
			break;
		case CGrondTree::DEAD:
			SetFrame(L"GroundTree_Dead", 15.f, 22, 1);
			SetInfo(103.f, 93.f);
			break;
		default:
			break;
		}
		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

BOOL CGrondTree::CheckWalk()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayer = m_tRect;
	CheckPlayer.left -= 450, CheckPlayer.right += 500, CheckPlayer.top -= 520;
	if (IntersectRect(&temp, &CheckPlayer, &PlayerRect)&&m_tFrame.fX==0)
	{
		ChangeState(WALK);
	}
	return 0;
}

BOOL CGrondTree::CheckAttack()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayerL = m_tRect;
	RECT CheckPlayerR = m_tRect;
	CheckPlayerL.left -= 200;
	CheckPlayerR.right += 200;
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

void CGrondTree::SetRect()
{
	rectGroundTree.left = m_tInfo.fX - 18;
	rectGroundTree.right = m_tInfo.fX + 18;
	rectGroundTree.top = m_tRect.top;
	rectGroundTree.bottom = m_tRect.bottom;
}

CGrondTree* CGrondTree::Create(float fStartX, float fStartY)
{
	CGrondTree* pInstance = new CGrondTree;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CGrondTree::Release()
{
}
