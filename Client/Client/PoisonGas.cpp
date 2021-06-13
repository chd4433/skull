#include "framework.h"
#include "PoisonGas.h"
#include "Player.h"

CPoisonGas::CPoisonGas()
{
}

CPoisonGas::~CPoisonGas()
{
	Release();
}

HRESULT CPoisonGas::Initialize(float fStartX, float fStartY, bool bDirection)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_bLeft = bDirection;
	m_fFrameCount = 0.f;
	if (m_bLeft)	SetFrame(L"PoisonGasR", 10.f, 9, 0);
	else			SetFrame(L"PoisonGasL", 10.f, 9, 0);
	return NOERROR;
}

INT CPoisonGas::Update(const float& fTimeDelta)
{
	UpdateRect();
	RECT temp;

	m_fFrameCount++;
	if (m_fFrameCount >= 9 * 5)	m_bOverRange = true;

	FrameMove(fTimeDelta);
	if (!m_bOverRange) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddBack(this);
	else
		return OBJ_DEAD; //CPoisonGas::~CPoisonGas();
	return 0;
}

VOID CPoisonGas::Render(HDC hDC)
{
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	UpdateRect();
	HDC hMemDC;
	if (m_bLeft)	hMemDC = m_pBmpMgr->FindBmp(L"PoisonGasR");
	else			hMemDC = m_pBmpMgr->FindBmp(L"PoisonGasL");
	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX, m_tRect.top,//이거 스크롤 값에 맞게 고쳐야함
		m_tInfo.fCX, m_tInfo.fCY,
		hMemDC,
		int(m_tFrame.fX) * m_tInfo.fCX, int(m_tFrame.fY) * m_tInfo.fCY,// 출력할 그림의 시작 좌표. 
		m_tInfo.fCX, m_tInfo.fCY,//그림의 전체 가로세로 크기 
		RGB(255, 0, 255));
}

CPoisonGas* CPoisonGas::Create(float fStartX, float fStartY, bool bDirection)
{
	CPoisonGas* pInstance = new CPoisonGas;
	if (FAILED(pInstance->Initialize(fStartX, fStartY, bDirection)))
		SafeDelete(pInstance);
	return pInstance;
}

void CPoisonGas::Release()
{
}
