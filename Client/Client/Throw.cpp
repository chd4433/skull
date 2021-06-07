#include "framework.h"
#include "Throw.h"

CThrow::CThrow()
{
}

CThrow::~CThrow()
{
	Release();
}

HRESULT CThrow::Initialize()
{
	return E_NOTIMPL;
}

INT CThrow::Update(const float& fTimeDelta)
{
	return 0;
}

VOID CThrow::Render(HDC hDC)
{
	return VOID();
}

HRESULT CThrow::ChangeState(STATE eState)
{
	return E_NOTIMPL;
}

void CThrow::Release()
{
}

CThrow* CThrow::Create()
{
	return nullptr;
}
