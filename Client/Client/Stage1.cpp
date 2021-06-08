#include "framework.h"
#include "Stage1.h"
#include "Player.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "Obj.h"
#include "Portal.h"

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
}
