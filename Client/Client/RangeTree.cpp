#include "framework.h"
#include "RangeTree.h"

CRangeTree::CRangeTree()
{
}

CRangeTree::~CRangeTree()
{
}

HRESULT CRangeTree::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 115.f;
	m_tInfo.fCY = 114.f;
	ChangeState(IDLE);
	return NOERROR;
}

INT CRangeTree::Update(const float& fTimeDelta)
{
	CheckIdle();
	CheckAttack();
	switch (m_eCurrState)
	{
	case CRangeTree::IDLE:
		break;
	case CRangeTree::ATTACK:
		break;
	default:
		break;
	}
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if (true) // �̰� �׸��� ���� �����ϴ� ����
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CRangeTree::Render(HDC hDC)
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

CRangeTree* CRangeTree::Create(float fStartX, float fStartY)
{
	CRangeTree* pInstance = new CRangeTree;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

HRESULT CRangeTree::ChangeState(STATE eState)
{
	m_eCurrState = eState;

	if (m_ePreState != m_eCurrState)
	{
		switch (m_eCurrState)
		{
		case CRangeTree::IDLE:
			// ó�� �� ���·� ���� ����� �ϴ°͵� ����� ����
			//m_tInfo.fCX = 197.f;
			//m_tInfo.fCY = 226.f;
			SetFrame(L"RangeTree_Idle", 10.f, 5, 1);
			SetInfo(115.f, 114.f);
			break;
		case CRangeTree::ATTACK:
			SetFrame(L"RangeTree_Attack", 4.f, 7, 1);
			SetInfo(140.f, 112.f);
			break;
		default:
			break;
		}
		m_ePreState = m_eCurrState;
	}

	return NOERROR;
}

BOOL CRangeTree::CheckIdle()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayer = m_tRect;
	CheckPlayer.left -= 150, CheckPlayer.right += 150;
	if (!IntersectRect(&temp, &CheckPlayer, &PlayerRect) && m_tFrame.fX == 0)
	{
		ChangeState(IDLE);
	}
	return 0;
}

BOOL CRangeTree::CheckAttack()
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	RECT CheckPlayer = m_tRect;
	CheckPlayer.left -= 150, CheckPlayer.right += 150;
	if (IntersectRect(&temp, &CheckPlayer, &PlayerRect) && m_tFrame.fX == 0)
	{
		if (!m_bMotionGetTick)
		{
			AttackMotion_Time = GetTickCount();
			m_bMotionGetTick = !m_bMotionGetTick;
		}
		if (AttackMotion_Time + 500 < GetTickCount())
			ChangeState(ATTACK);
	}
	return 0;
}

void CRangeTree::SetRect()
{
}

void CRangeTree::Release()
{
}