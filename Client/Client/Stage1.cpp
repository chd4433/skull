#include "framework.h"
#include "Stage1.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "Portal.h"
#include "GrondTree.h"
#include "RangeTree.h"
#include "MovingTree.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

HRESULT CStage1::Initialize()
{
	CScrollManager::Get_ScrollX() = 0;
	CSceneMgr::GetInstance()->Get_ChangeScene() = FALSE;
	//CScrollManager::Set_ScrollY(0);
	CScene::Initialize();
	CObj* pPlayer = CPlayer::Create();
	static_cast<CPlayer*>(pPlayer)->Set_Scene(SCENE_STAGE1);
	m_pObjMgr->Add(PLAYER, pPlayer);
	//m_pObjMgr->Add(PORTAL, CPortal::Create(2126, 450));
	//CObj* pGroundMonster = CGrondTree::Create(1000, 495);
	//pGroundMonster->SetObjScene(SCENE_STAGE1);
	CObj* pGroundMonster = CMovingTree::Create(1000, 495);
	pGroundMonster->SetObjScene(SCENE_STAGE1);
	m_pObjMgr->Add(MONSTER, pGroundMonster);
	CObj* pGroundMonster2 = CGrondTree::Create(1600, 495);
	CObj* pGroundMonster3 = CGrondTree::Create(2200, 495);
	pGroundMonster2->SetObjScene(SCENE_STAGE1);
	pGroundMonster3->SetObjScene(SCENE_STAGE1);
	//m_pObjMgr->Add(MONSTER, pGroundMonster2);
	//m_pObjMgr->Add(MONSTER, pGroundMonster3);
	//m_pObjMgr->Add(MONSTER, CRangeTree::Create(805, 313));
	CObj* pPortal = CPortal::Create(2120, 225);
	pPortal->SetObjScene(SCENE_STAGE1);
	m_pObjMgr->Add(PORTAL, pPortal);
	//CCollisionMgr::GetInstance()->LoadCollisionFromPath(L"../Binary/Map2Collision.txt");
	return NOERROR;
}

INT CStage1::Update(const float& fTimeDelta)
{
	m_pObjMgr->Update(fTimeDelta);
	return 0;
}

VOID CStage1::Render(HDC hDC)
{
	int iScrollX = CScrollManager::Get_ScrollX();
	int iScrollY = CScrollManager::Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Map2");
	BitBlt(hDC, iScrollX, iScrollY, 2400, 600, hMemDC, 0, 0, SRCCOPY);
	if (m_pSCenceMgr->Get_ChangeScene())
	{
		m_pSCenceMgr->ChangeScene(m_pSCenceMgr->Get_NextScene());
	}
	else
		m_pRenderMgr->Render(hDC);
}

CStage1* CStage1::Create()
{
	CStage1* pInstance = new CStage1();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CStage1::Release()
{
	m_pObjMgr->Reset();
	m_pRenderMgr->Clear();
}
