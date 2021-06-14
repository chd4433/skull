#include "framework.h"
#include "SwordmanAttack.h"
#include "Player.h"

CSwordmanAttack::CSwordmanAttack()
{
}

CSwordmanAttack::~CSwordmanAttack()
{
	Release();
}

HRESULT CSwordmanAttack::Initialize(float fCurrX, float fCurrY, int motion, bool isLeft)
{
	CObj::Initialize();
	m_tInfo.fX = fCurrX;
	m_tInfo.fY = fCurrY;
	m_iMotion = motion;//
	switch (motion) {
	case 0:
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		if (!isLeft)	SetFrame(L"S_Attack1R", 15.f, 5, 1, 0, 0);
		else			SetFrame(L"S_Attack1L", 15.f, 5, 1, 0, 0);
		break;
	case 1:
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 40.f;
		if (!isLeft)	SetFrame(L"S_Attack2R", 15.f, 4, 1, 0, 0);
		else			SetFrame(L"S_Attack2L", 15.f, 4, 1, 0, 0);
		break;
	case 2:
		m_tInfo.fCX = 60.f;
		m_tInfo.fCY = 40.f;
		if (!isLeft)	SetFrame(L"S_Attack3R", 15.f, 6, 1, 0, 0);
		else			SetFrame(L"S_Attack3L", 15.f, 6, 1, 0, 0);
		break;
	}
	m_bframe = FALSE;
	return NOERROR;
}

INT CSwordmanAttack::Update(const float& fTimeDelta)
{
	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0) {
		m_bframe = TRUE;
	}
	if (m_bframe)
		return OBJ_DEAD;
	if (b_ChangeSceneDead)
		return OBJ_DEAD;

	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CSwordmanAttack::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
}

CSwordmanAttack* CSwordmanAttack::Create(float fCurrX, float fCurrY, int motion, bool isLeft)
{
	CSwordmanAttack* pInstance = new CSwordmanAttack;
	if (FAILED(pInstance->Initialize(fCurrX, fCurrY, motion, isLeft)))
		SafeDelete(pInstance);
	return pInstance;
}

void CSwordmanAttack::Release()
{
}
