#include "framework.h"
#include "SwordmanSkill.h"
#include "Player.h"

CSwordmanSkill::CSwordmanSkill()
{
}

CSwordmanSkill::~CSwordmanSkill()
{
	Release();
}

HRESULT CSwordmanSkill::Initialize(float fCurrX, float fCurrY, bool isLeft)
{
	CObj::Initialize();
	m_tInfo.fX = fCurrX;
	m_tInfo.fY = fCurrY;
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 40.f;
	if (!isLeft)	SetFrame(L"S_SkillR", 15.f, 6, 1, 0, 0);
	else			SetFrame(L"S_SkillL", 15.f, 6, 1, 0, 0);

	m_fDashLen = 0.f;
	m_bLeft = isLeft;
	m_bframe = FALSE;
	return NOERROR;
}

INT CSwordmanSkill::Update(const float& fTimeDelta)
{
	if (m_fDashLen < 180) {
		if (m_bLeft)	m_tInfo.fX -= 15.f;
		else			m_tInfo.fX += 15.f;
		m_fDashLen += 15.f;
		cout << "fX: " << m_tInfo.fX << endl;
	}

	FrameMove(fTimeDelta);
	if (m_tFrame.fX == 0) {
		m_bframe = TRUE;
	}
	if (m_bframe) {
		return OBJ_DEAD;
	}
	if (b_ChangeSceneDead)
		return OBJ_DEAD;

	if (true) // 이걸 그릴지 말지 결정하는 조건
		m_pRenderMgr->AddFront(this);

	return 0;
}

VOID CSwordmanSkill::Render(HDC hDC)
{
	UpdateRect();
	int iScrollX = (int)CScrollManager::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollManager::GetInstance()->Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(m_tFrame.strFrameKey);
}

CSwordmanSkill* CSwordmanSkill::Create(float fCurrX, float fCurrY, bool isLeft)
{
	CSwordmanSkill* pInstance = new CSwordmanSkill;
	if (FAILED(pInstance->Initialize(fCurrX, fCurrY, isLeft)))
		SafeDelete(pInstance);
	return pInstance;
}

void CSwordmanSkill::Release()
{
}
