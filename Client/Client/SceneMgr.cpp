#include "framework.h"
#include "SceneMgr.h"

#include "SceneLogo.h"
#include "TurorialStage.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Last.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

INT CSceneMgr::Update(const float& fTimeDelta)
{
	return m_pScene->Update(fTimeDelta);
}

VOID CSceneMgr::Render(HDC hdc)
{
	return m_pScene->Render(hdc);
}

HRESULT CSceneMgr::ChangeScene(SCENE_ID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		SafeDelete(m_pScene);

		switch (eID)
		{
		case SCENE_LOGO:
			m_pScene = CSceneLogo::Create();
			break;
		case SCENE_TUTORIAL:
			m_pScene = CTutorialStage::Create();
			break;
		case SCENE_STAGE1:
			m_pScene = CStage1::Create();
			break;
		case SCENE_STAGE2:
			m_pScene = CStage2::Create();
			break;
		case SCENE_END:
			m_pScene = CLast::Create();
			break;
		default:
			break;
		}

		if (!m_pScene)
			return E_FAIL;

		m_ePreScene = m_eCurScene;
	}

	return NOERROR;
}

HRESULT CSceneMgr::Change_NextScene()
{
	m_eNextScene = SCENE_ID(m_ePreScene + 1);
	return NOERROR;
}

HRESULT CSceneMgr::Change_LastScene()
{
	m_eNextScene = SCENE_ID(SCENE_END);
	return NOERROR;
}

HRESULT CSceneMgr::Change_GameOverScene()
{
	m_eNextScene = SCENE_ID(SCENE_GAMEOVER);
	return NOERROR;
}

void CSceneMgr::Release()
{
}
