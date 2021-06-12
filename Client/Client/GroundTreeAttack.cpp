#include "framework.h"
#include "GroundTreeAttack.h"

CGroundTreeAttack::CGroundTreeAttack()
{
}

CGroundTreeAttack::~CGroundTreeAttack()
{
	Release();
}

HRESULT CGroundTreeAttack::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	return E_NOTIMPL;
}

INT CGroundTreeAttack::Update(const float& fTimeDelta)
{
	return 0;
}

VOID CGroundTreeAttack::Render(HDC hDC)
{
	return VOID();
}

void CGroundTreeAttack::Release()
{
}
