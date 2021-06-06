#include "framework.h"
#include "Scene.h"


CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Initialize()
{
	m_pObjMgr = CObjMgr::GetInstance();
	m_pKeyMgr = CKeyMgr::GetInstance();
	m_pBmpMgr = CBitmapMgr::GetInstance();
	m_pRenderMgr = CRenderMgr::GetInstance();
	m_pSCenceMgr = CSceneMgr::GetInstance();
	m_pScrollMgr = CScrollManager::GetInstance();

	return NOERROR;
}

INT CScene::Update(const float& fTimeDelta)
{
	return 0;
}

VOID CScene::Render(HDC hDC)
{
	return VOID();
}

void CScene::Release()
{
}
