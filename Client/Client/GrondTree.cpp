#include "framework.h"
#include "GrondTree.h"
#include "Player.h"

CGrondTree::CGrondTree()
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
	ChangeState(IDLE);
	return NOERROR;
}

INT CGrondTree::Update(const float& fTimeDelta)
{
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
	if (IntersectRect(&temp, &m_tRect, &PlayerRect))
	{
		ChangeState(WALK);
	}
	return 0;
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
