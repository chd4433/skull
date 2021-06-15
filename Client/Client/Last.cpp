#include "framework.h"
#include "Last.h"

CLast::CLast()
{
}

CLast::~CLast()
{
	Release();
}

HRESULT CLast::Initialize()
{
	CSceneMgr::GetInstance()->Get_ChangeScene() = FALSE;
	//CScrollManager::Set_ScrollY(0);
	CScene::Initialize();
	strName = L"Last1";
	return NOERROR;
}

INT CLast::Update(const float& fTimeDelta)
{
	if (m_pKeyMgr->KeyDown((KEY_ENTER)))
	{
		strName = L"Last2";
	}
	return 0;
}

void CLast::Render(HDC hDC)
{
	HDC hMemDC = m_pBmpMgr->FindBmp(strName);
	BitBlt(hDC, 0, 0, 800, 600, hMemDC, 0, 0, SRCCOPY);
	//m_pRenderMgr->Render(hDC);
}

CLast* CLast::Create()
{
	CLast* pInstance = new CLast();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CLast::Release()
{
}
