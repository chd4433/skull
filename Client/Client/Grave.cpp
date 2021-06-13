#include "framework.h"
#include "Grave.h"
#include "Player.h"

CGrave::CGrave()
{
}

CGrave::~CGrave()
{
}

HRESULT CGrave::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 97.f;
	m_tInfo.fCY = 49.f;
	SetFrame(L"Grave", 10.f, 10, 1);
	m_bInterectGrave = FALSE;
	m_bFramemove = TRUE;
	return NOERROR;
}

INT CGrave::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();
	if (IntersectRect(&temp, &m_tRect, &PlayerRect))
	{
		if (m_pKeyMgr->KeyDown(KEY_INTERECT))
		{
			m_bInterectGrave = TRUE;
			//dynamic_cast<CPlayer*>(m_pObjMgr->Get_Player())->ChangeCharacter();
		}
	}
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	if (m_bInterectGrave&&m_bFramemove)
	{
		FrameMove(fTimeDelta);
		if (m_tFrame.fX == 0)
			m_bFramemove = FALSE;
	}
	if (m_bFramemove) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CGrave::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CGrave* CGrave::Create(float fStartX, float fStartY)
{
	CGrave* pInstance = new CGrave;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CGrave::Release()
{
}
