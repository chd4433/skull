#include "framework.h"
#include "CCloseAttack2.h"

CCloseAttack2::CCloseAttack2()
{
}

CCloseAttack2::~CCloseAttack2()
{
	Release();
}

HRESULT CCloseAttack2::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 139.f;
	m_tInfo.fCY = 108.f;
	m_bframe = FALSE;
	SetFrame(L"Boss_AttackL_B", 10.f, 4, 1);
	return NOERROR;
}

INT CCloseAttack2::Update(const float& fTimeDelta)
{
	UpdateRect();
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		m_bframe = TRUE;
	if (m_bframe)
		return OBJ_DEAD;
	if (b_ChangeDeadCloseAtt)
		return OBJ_DEAD;
	return 0;
}

VOID CCloseAttack2::Render(HDC hDC)
{
}

CCloseAttack2* CCloseAttack2::Create(float fStartX, float fStartY)
{
	CCloseAttack2* pInstance = new CCloseAttack2;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CCloseAttack2::Release()
{
}
