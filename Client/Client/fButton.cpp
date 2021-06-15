#include "framework.h"
#include "fButton.h"

CfButton::CfButton()
{
}

CfButton::~CfButton()
{
	Release();
}

HRESULT CfButton::Initialize(float fStartX, float fStartY)
{
	CObj::Initialize();
	m_tInfo.fX = fStartX;
	m_tInfo.fY = fStartY;
	m_tInfo.fCX = 13.f;
	m_tInfo.fCY = 12.f;
	SetFrame(L"F", 10.f, 1, 1);
	return NOERROR;
}

INT CfButton::Update(const float& fTimeDelta)
{
	return 0;
}

VOID CfButton::Render(HDC hDC)
{
	return VOID();
}

CfButton* CfButton::Create(float fStartX, float fStartY)
{
	return nullptr;
}

VOID CfButton::TargetPlayer()
{
	return VOID();
}

void CfButton::Release()
{
}
