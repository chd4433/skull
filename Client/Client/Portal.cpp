#include "framework.h"
#include "Portal.h"
#include "Player.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
	Release();
}

HRESULT CPortal::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 215.f;
	m_tInfo.fCY = 159.f;
	SetFrame(L"Portal", 10.f, 8, 1);
	return NOERROR;
}

INT CPortal::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();
	if (IntersectRect(&temp, &m_tRect, &PlayerRect))
	{
		m_bRenderUI = true;
		if (m_pKeyMgr->KeyDown(KEY_INTERECT))
		{
			CSceneMgr::GetInstance()->Change_NextScene();
			CSceneMgr::GetInstance()->Get_ChangeScene() = TRUE;
		}
	}
	else
		m_bRenderUI = false;
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CPortal::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Portal");
	GdiTransparentBlt(hDC,
		m_tRect.left+iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CPortal* CPortal::Create(float fStartX, float fStartY)
{
	CPortal* pInstance = new CPortal;
	if (FAILED(pInstance->Initialize(fStartX,fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CPortal::Release()
{
}
