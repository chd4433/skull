#include "framework.h"
#include "CloseAttack1.h"

CCloseAttack1::CCloseAttack1()
{
}

CCloseAttack1::~CCloseAttack1()
{
	Release();
}

HRESULT CCloseAttack1::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 115.f;
	m_tInfo.fCY = 94.f;
	m_bframe = FALSE;
	SetFrame(L"Boss_AttackL_A", 10.f, 9, 1);
	return NOERROR;
}

INT CCloseAttack1::Update(const float& fTimeDelta)
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

VOID CCloseAttack1::Render(HDC hDC)
{
}

CCloseAttack1* CCloseAttack1::Create(float fStartX, float fStartY)
{
	CCloseAttack1* pInstance = new CCloseAttack1;
	if (FAILED(pInstance->Initialize(fStartX, fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CCloseAttack1::Release()
{
}
