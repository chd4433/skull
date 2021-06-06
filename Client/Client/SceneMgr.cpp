#include "framework.h"
#include "SceneMgr.h"

#include "SceneLogo.h"
#include "TurorialStage.h"

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

void CSceneMgr::Release()
{
}
