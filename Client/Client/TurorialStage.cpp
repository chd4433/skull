#include "framework.h"
#include "TurorialStage.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "Portal.h"

CTutorialStage::CTutorialStage()
{
}

CTutorialStage::~CTutorialStage()
{
	Release();
}

HRESULT CTutorialStage::Initialize()
{
	CScene::Initialize();
	CObj* pPlayer = CPlayer::Create();
	static_cast<CPlayer*>(pPlayer)->Set_Scene(SCENE_TUTORIAL);
	m_pObjMgr->Add(PLAYER, pPlayer);
	CObj* pPortal = CPortal::Create(1379, 290);
	pPortal->SetObjScene(SCENE_TUTORIAL);
	m_pObjMgr->Add(PORTAL, pPortal);

	//pObj = CPortal::Create(2231.25f, 357.354f);
	//m_pGameMgr->Add_GameObject(MAP, pObj);

	//if (FAILED(m_pObjMgr->Set_CurrMap(m_pMap)))
	//	return E_FAIL;

	return NOERROR;
}

INT CTutorialStage::Update(const float& fTimeDelta)
{
	m_pObjMgr->Update(fTimeDelta);
	//if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	//{
	//	CScrollManager::Set_ScrollX(5);
	//}
	//if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	//{
	//	CScrollManager::Set_ScrollX(-5);
	//}
	//if (m_pKeyMgr->KeyPressing(KEY_UP))
	//{
	//	CScrollManager::Set_ScrollX(5);
	//}
	//if (m_pKeyMgr->KeyPressing(KEY_DOWN))
	//{
	//	CScrollManager::Set_ScrollX(5);
	//}
	return 0;
}

VOID CTutorialStage::Render(HDC hDC)
{
	int iScrollX = CScrollManager::Get_ScrollX();
	int iScrollY = CScrollManager::Get_ScrollY();
	//CObj* pPlayer = CPlayer::Create();
	//
	//INFO iScroll = static_cast<CPlayer*>(pPlayer)->GetInfo(); //?
	//int iScrollY = CScrollManager::Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Map1");
	BitBlt(hDC, iScrollX, iScrollY, 1600, 600, hMemDC, 0, 0, SRCCOPY);
	if (m_pSCenceMgr->Get_ChangeScene())
	{
		m_pSCenceMgr->ChangeScene(m_pSCenceMgr->Get_NextScene());
	}
	else
		m_pRenderMgr->Render(hDC);
	//if (m_pKeyMgr->KeyDown(KEY_NEXTSTAGE))
	//{
	//	m_pSceneMgr->ChangeScene(CSceneMgr::SCENE_STAGE1);
	//	return NOERROR;
	//}
	
}

CTutorialStage* CTutorialStage::Create()
{
	CTutorialStage* pInstance = new CTutorialStage();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CTutorialStage::Release()
{
	m_pObjMgr->Reset();
	m_pRenderMgr->Clear();
}
