#include "framework.h"
#include "DiePopUp.h"
#include "Player.h"

CDiePopUp::CDiePopUp()
{
}

CDiePopUp::~CDiePopUp()
{
	Release();
}

HRESULT CDiePopUp::Initialize(int Count)
{
	CObj::Initialize();
	m_tInfo.fX = 400;
	m_tInfo.fY = 200;
	m_tInfo.fCX = 160.f;
	m_tInfo.fCY = 400.f;

	m_iCount = Count;
	cout << m_iCount << endl;
	switch (m_iCount) {
	case 4:
		SetFrame(L"Frame_GameOver4", 10.f, 1, 0);
		break;
	case 3:
		SetFrame(L"Frame_GameOver3", 10.f, 1, 0);
		break;
	case 2:
		SetFrame(L"Frame_GameOver2", 10.f, 1, 0);
		break;
	case 1:
		SetFrame(L"Frame_GameOver1", 10.f, 1, 0);
		break;
	default:
		SetFrame(L"Frame_GameOver5", 10.f, 1, 0);
	}

	return NOERROR;
}

INT CDiePopUp::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 400 - iScrollX;
	FrameMove(fTimeDelta);

	if (!m_bGetTick)
	{
		Popup_Time = GetTickCount();
		m_bGetTick = !m_bGetTick;
	}
	if (m_iCount >= 0 && Popup_Time + 1050 < GetTickCount())
	{
		m_bGetTick = !m_bGetTick;
		return OBJ_DEAD;
	}

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CDiePopUp::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver5");
	switch (m_iCount) {
	case 4:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver4");
		break;
	case 3:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver3");
		break;
	case 2:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver2");
		break;
	case 1:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver1");
		break;
	default:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_GameOver5");
	}
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CDiePopUp* CDiePopUp::Create(int Count)
{
	CDiePopUp* pInstance = new CDiePopUp;
	if (FAILED(pInstance->Initialize(Count)))
		SafeDelete(pInstance);
	return pInstance;
}

void CDiePopUp::Release()
{
}
