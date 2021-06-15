#include "framework.h"
#include "DistnaceAttack.h"

CDistnaceAttack::CDistnaceAttack()
{
}

CDistnaceAttack::~CDistnaceAttack()
{
	Release();
}

HRESULT CDistnaceAttack::Initialize(float fStartX, float fStartY,BOOL bRight)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 70.f;
	m_tInfo.fCY = 70.f;
	SetFrame(L"Boss_Ball", 10.f, 8, 1);
	m_bframe = FALSE;
	m_bRight = bRight;
	//TargetPlayer();
	//iCollisonFrame = 0;
	return NOERROR;
}

INT CDistnaceAttack::Update(const float& fTimeDelta)
{
	if (!m_bRight)
		m_tInfo.fX-=2;
	else
		m_tInfo.fX+=2;
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		return OBJ_DEAD;
	if (b_ChangeSceneDead)
		return OBJ_DEAD;
	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CDistnaceAttack::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top + iScrollY ,
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CDistnaceAttack* CDistnaceAttack::Create(float fStartX, float fStartY, BOOL bRight)
{
	CDistnaceAttack* pInstance = new CDistnaceAttack;
	if (FAILED(pInstance->Initialize(fStartX,fStartY,bRight)))
		SafeDelete(pInstance);
	return pInstance;
}

void CDistnaceAttack::Release()
{
}
