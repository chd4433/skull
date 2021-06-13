#include "framework.h"
#include "Throw.h"
#include "Player.h"

CThrow::CThrow()
{
}

CThrow::~CThrow()
{
	Release();
}

HRESULT CThrow::Initialize(float fStartX, float fStartY, bool bDirection)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fDistance = 0.f;
	m_bLeft = bDirection;
	SetFrame(L"Potion1", 10.f, 4, 1);
	return NOERROR;
}

INT CThrow::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	if (m_bLeft)	m_tInfo.fX -= 5;
	else			m_tInfo.fX += 5;
	m_fDistance += 5;
	if (m_fDistance >= 200)	m_bOverRange = true;

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if (!m_bOverRange) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	else
		CThrow::~CThrow();
	return 0;
}

VOID CThrow::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Posion1");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CThrow* CThrow::Create(float fStartX, float fStartY, bool bDirection)
{
	CThrow* pInstance = new CThrow;
	if (FAILED(pInstance->Initialize(fStartX, fStartY, bDirection)))
		SafeDelete(pInstance);
	return pInstance;
}

void CThrow::Release()
{
}
