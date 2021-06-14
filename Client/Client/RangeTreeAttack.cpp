#include "framework.h"
#include "RangeTreeAttack.h"

CRangeTreeAttack::CRangeTreeAttack()
{
}

CRangeTreeAttack::~CRangeTreeAttack()
{
	Release();
}

HRESULT CRangeTreeAttack::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 124.f;
	m_tInfo.fCY = 58.f;
	m_bframe = FALSE;
	SetFrame(L"RangeTree_Attack", 4.f, 7, 1);
	return NOERROR;
}

INT CRangeTreeAttack::Update(const float& fTimeDelta)
{
	UpdateRect();
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0)
		m_bframe = TRUE;
	if (m_bframe)
		return OBJ_DEAD;
	return 0;
}

VOID CRangeTreeAttack::Render(HDC hDC)
{
}

CRangeTreeAttack* CRangeTreeAttack::Create(float fStartX, float fStartY)
{
	CRangeTreeAttack* pInstance = new CRangeTreeAttack;
	if (FAILED(pInstance->Initialize(fStartX,fStartY)))
		SafeDelete(pInstance);
	return pInstance;
}

void CRangeTreeAttack::Release()
{
}
