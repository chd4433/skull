#include "framework.h"
#include "TutorialInform1.h"
#include "Player.h"

CTutorialInform1::CTutorialInform1()
{
}

CTutorialInform1::~CTutorialInform1()
{
	Release();
}

HRESULT CTutorialInform1::Initialize()
{
	CObj::Initialize();
	m_tInfo.fX = 400;
	m_tInfo.fY = 250;
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 90.f;

	SetFrame(L"Inform_Tutorial1", 10.f, 1, 0);

	return NOERROR;
}

INT CTutorialInform1::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();

	m_tInfo.fX = 400 - iScrollX;
	FrameMove(fTimeDelta);

	if (m_pKeyMgr->KeyDown(KEY_ENTER))
		return OBJ_DEAD;

	m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CTutorialInform1::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Inform_Tutorial1");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CTutorialInform1* CTutorialInform1::Create()
{
	CTutorialInform1* pInstance = new CTutorialInform1;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

void CTutorialInform1::Release()
{
}
