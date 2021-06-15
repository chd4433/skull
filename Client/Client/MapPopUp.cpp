#include "framework.h"
#include "MapPopUp.h"
#include "Player.h"

CMapPopUp::CMapPopUp()
{
}

CMapPopUp::~CMapPopUp()
{
	Release();
}

HRESULT CMapPopUp::Initialize(SCENE_ID curr)
{
	CObj::Initialize();
	m_tInfo.fX = 400;
	m_tInfo.fY = 50;
	m_tInfo.fCX = 220.f;
	m_tInfo.fCY = 80.f;

	current = curr;
	switch (current) {
	case SCENE_TUTORIAL:
		SetFrame(L"Frame_Tutorial", 10.f, 1, 0);
		break;
	case SCENE_STAGE1:
		SetFrame(L"Frame_Stage1", 10.f, 1, 0);
		break;
	case SCENE_STAGE2:
		SetFrame(L"Frame_Stage2", 10.f, 1, 0);
		break;
	}

	return NOERROR;
}

INT CMapPopUp::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 400 - iScrollX;
	FrameMove(fTimeDelta);
	// 1초 후에 삭제
	if (!m_bGetTick)
	{
		BossState_Timer = GetTickCount();
		m_bGetTick = !m_bGetTick;
	}
	if (BossState_Timer + 1000 < GetTickCount())
	{
		m_tInfo.fY -= 3;
		if (m_tInfo.fY <= 0) {
			m_bGetTick = !m_bGetTick;
			return OBJ_DEAD;
		}
	}

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CMapPopUp::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Frame_Tutorial");
	switch (current) {
	case SCENE_TUTORIAL:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_Tutorial");
		break;
	case SCENE_STAGE1:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_Stage1");
		break;
	case SCENE_STAGE2:
		hMemDC = m_pBmpMgr->FindBmp(L"Frame_Stage2");
		break;
	}
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CMapPopUp* CMapPopUp::Create(SCENE_ID curr)
{
	CMapPopUp* pInstance = new CMapPopUp;
	if (FAILED(pInstance->Initialize(curr)))
		SafeDelete(pInstance);
	return pInstance;
}

void CMapPopUp::Release()
{
}
