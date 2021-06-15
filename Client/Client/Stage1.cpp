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
	CObj* pPlayer = CPlayer::Create(50, 500, 500, true, true);
	static_cast<CPlayer*>(pPlayer)->Set_Scene(SCENE_STAGE1);
	m_pObjMgr->Add(PLAYER, pPlayer);
	CObj* pGroundMonster = CGrondTree::Create(1000, 495);
	CObj* pGroundMonster2 = CGrondTree::Create(1600, 495);
	CObj* pGroundMonster3 = CGrondTree::Create(2200, 495);
	CObj* pGroundMonster4 = CGrondTree::Create(3000, 495);
	CObj* pGroundMonster5 = CGrondTree::Create(4000, 495);
	CObj* pGroundMonster6 = CGrondTree::Create(4500, 495);
	CObj* pMovingMonster = CMovingTree::Create(1000, 495);
	CObj* pMovingMonster2 = CMovingTree::Create(2000, 495);
	CObj* pMovingMonster3 = CMovingTree::Create(2900, 495);
	CObj* pMovingMonster4 = CMovingTree::Create(3200, 495);
	CObj* pMovingMonster5 = CMovingTree::Create(2300, 495);
	pGroundMonster->SetObjScene(SCENE_STAGE1);
	pGroundMonster2->SetObjScene(SCENE_STAGE1);
	pGroundMonster3->SetObjScene(SCENE_STAGE1);
	pGroundMonster4->SetObjScene(SCENE_STAGE1);
	pGroundMonster5->SetObjScene(SCENE_STAGE1);
	pGroundMonster6->SetObjScene(SCENE_STAGE1);
	pMovingMonster->SetObjScene(SCENE_STAGE1);
	pMovingMonster2->SetObjScene(SCENE_STAGE1);
	pMovingMonster3->SetObjScene(SCENE_STAGE1);
	pMovingMonster4->SetObjScene(SCENE_STAGE1);
	pMovingMonster5->SetObjScene(SCENE_STAGE1);
	m_pObjMgr->Add(MONSTER, pMovingMonster);
	m_pObjMgr->Add(MONSTER, pMovingMonster2);
	m_pObjMgr->Add(MONSTER, pMovingMonster3);
	m_pObjMgr->Add(MONSTER, pMovingMonster4);
	m_pObjMgr->Add(MONSTER, pMovingMonster5);
	m_pObjMgr->Add(MONSTER, pGroundMonster);
	m_pObjMgr->Add(MONSTER, pGroundMonster2);
	m_pObjMgr->Add(MONSTER, pGroundMonster3);
	m_pObjMgr->Add(MONSTER, pGroundMonster4);
	m_pObjMgr->Add(MONSTER, pGroundMonster5);
	m_pObjMgr->Add(MONSTER, pGroundMonster6);
	m_pObjMgr->Add(MONSTER, CRangeTree::Create(805, 313));
	m_pObjMgr->Add(MONSTER, CRangeTree::Create(2105, 240));
	m_pObjMgr->Add(MONSTER, CRangeTree::Create(3075, 235));
	
	
	
	CObj* pPortal = CPortal::Create(4555, 460);
	pPortal->SetObjScene(SCENE_STAGE1);
	m_pObjMgr->Add(PORTAL, pPortal);
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
	BitBlt(hDC, iScrollX, iScrollY, 4800, 600, hMemDC, 0, 0, SRCCOPY);
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
