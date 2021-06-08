#include "framework.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "BitmapMgr.h"
#include "FrameMgr.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

HRESULT CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_pObjMgr = CObjMgr::GetInstance();
	m_pKeyMgr = CKeyMgr::GetInstance();
	m_pBmpMgr = CBitmapMgr::GetInstance();
	m_pSceneMgr = CSceneMgr::GetInstance();
	m_pCollisionMgr = CCollisionMgr::GetInstance();
	if (FAILED(CBitmapMgr::GetInstance()->LoadBmpFromPath(L"../Binary/Path.txt")))
		return E_FAIL;
	if (FAILED(m_pSceneMgr->ChangeScene(SCENE_LOGO)))//무조건 마지막
		return E_FAIL;


	return NOERROR;
}

INT CMainGame::Update(const float& fTimeDelta)
{
	m_pSceneMgr->Update(fTimeDelta);
	m_pKeyMgr->UpdateKey();

	return 0;
}

VOID CMainGame::Render()
{
	m_hBackDC = m_pBmpMgr->FindBmp(L"Back");
	m_hMemDC = m_pBmpMgr->FindBmp(L"Back2");
	BitBlt(m_hBackDC, 0, 0, WINCX, WINCY, m_hMemDC, 0, 0, SRCCOPY);

	// 더블버퍼링
	m_pSceneMgr->Render(m_hBackDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, SRCCOPY);
}

CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;
	// 이니셜라이즈 실행하고 망하면 지워
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

VOID CMainGame::Release()
{
	CFrameMgr::GetInstance()->DestroyInstance();
	CKeyMgr::GetInstance()->DestroyInstance();
	CBitmapMgr::GetInstance()->DestroyInstance();
	CScrollManager::GetInstance()->DestroyInstance();
	CSceneMgr::GetInstance()->DestroyInstance();
	CRenderMgr::GetInstance()->DestroyInstance();
	CObjMgr::GetInstance()->DestroyInstance();
}
