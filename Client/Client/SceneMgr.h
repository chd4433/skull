#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)


private:
	CSceneMgr();
	~CSceneMgr();
public:
	SCENE_ID GetNextScene() { return m_eNextScene; }
public:
	INT	Update(const float& fTimeDelta);
	VOID	Render(HDC hdc);
public:
	BOOL& Get_ChangeScene() { return m_bChangeScene; }
	SCENE_ID& Get_NextScene() { return m_eNextScene; }
public:
	HRESULT	ChangeScene(SCENE_ID eID);
	HRESULT Change_NextScene();

private:
	CScene* m_pScene = nullptr;
	SCENE_ID m_ePreScene = SCENE_END;
	SCENE_ID m_eCurScene = SCENE_END;
	SCENE_ID m_eNextScene = SCENE_END;
	BOOL m_bChangeScene = false;

private:
	void Release();
};


