#include "framework.h"
#include "Energyball.h"
#include "Player.h"

CEnergyball::CEnergyball()
{
}

CEnergyball::~CEnergyball()
{
	Release();
}

HRESULT CEnergyball::Initialize(float fStartX, float fStartY, bool bDirection)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fDistance = 0.f;
	m_bLeft = bDirection;
	SetFrame(L"A_Energyball", 10.f, 1, 0);
	return NOERROR;
}

INT CEnergyball::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;
	RECT PlayerRect = m_pObjMgr->Get_Player()->GetRect();//CPlayer::Create()->GetRectPlayer();

	if (m_bLeft)	m_tInfo.fX -= 7;
	else			m_tInfo.fX += 7;
	m_fDistance += 7;
	if (m_fDistance >= 203)	m_bOverRange = true;

	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	FrameMove(fTimeDelta);
	if(b_ChangeSceneDead||m_bOverRange)
		return OBJ_DEAD;
	if (!m_bOverRange) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	return 0;
}

VOID CEnergyball::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"A_Energyball");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CEnergyball* CEnergyball::Create(float fStartX, float fStartY, bool bDirection)
{
	CEnergyball* pInstance = new CEnergyball;
	if (FAILED(pInstance->Initialize(fStartX, fStartY, bDirection)))
		SafeDelete(pInstance);
	return pInstance;
}

void CEnergyball::Release()
{
}
