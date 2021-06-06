#include "framework.h"
#include "SceneLogo.h"
#include "Player.h"

CSceneLogo::CSceneLogo()
{
}

CSceneLogo::~CSceneLogo()
{
	Release();
}

HRESULT CSceneLogo::Initialize()
{
	CScene::Initialize();//지 부모꺼 부르기 (공통된거 귀찮아서 깡통 만들엇자나 ㅇㅋ?)

	//m_pObjMgr->Add(PLAYER, CPlayer::Create());  //이건 스테이지에서

	return NOERROR;
}

INT CSceneLogo::Update(const float& fTimeDelta)
{
	//m_pObjMgr->Update(fTimeDelta);
	return 0;
}

VOID CSceneLogo::Render(HDC hDC)
{
	
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Menu");
	StretchBlt(hDC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, 1280, 720, SRCCOPY);
	if (m_pKeyMgr->KeyDown((KEY_ENTER)))
	{
		m_pSCenceMgr->ChangeScene(SCENE_TUTORIAL);
	}
	//m_pRenderMgr->Render(hDC);

}

void CSceneLogo::Release()
{
	m_pObjMgr->Reset();
	m_pRenderMgr->Clear();//씬마다 넣어주기
}

CSceneLogo* CSceneLogo::Create()
{
	CSceneLogo* pInstance = new CSceneLogo;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
