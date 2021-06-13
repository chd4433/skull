#include "framework.h"
#include "Stage2.h"
#include "Player.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

HRESULT CStage2::Initialize()
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

INT CStage2::Update(const float& fTimeDelta)
{
	m_pObjMgr->Update(fTimeDelta);
	return 0;
}

void CStage2::Render(HDC hDC)
{
	int iScrollX = CScrollManager::Get_ScrollX();
	int iScrollY = CScrollManager::Get_ScrollY();
	HDC hMemDC = m_pBmpMgr->FindBmp(L"Map3");
	BitBlt(hDC, iScrollX, iScrollY, 1600, 750, hMemDC, 0, 0, SRCCOPY);
	if (m_pSCenceMgr->Get_ChangeScene())
	{
		m_pSCenceMgr->ChangeScene(m_pSCenceMgr->Get_NextScene());
	}
	else
		m_pRenderMgr->Render(hDC);
}

CStage2* CStage2::Create()
{
	CStage2* pInstance = new CStage2();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CStage2::Release()
{
	m_pObjMgr->Reset();
	m_pRenderMgr->Clear();
}
