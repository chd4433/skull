#pragma once

class CScene;
class CSceneMgr
{
	DECLARE_SINGLETON(CSceneMgr)


private:
	CSceneMgr();
	~CSceneMgr();

public:
	INT	Update(const float& fTimeDelta);
	VOID	Render(HDC hdc);

public:
	HRESULT	ChangeScene(SCENE_ID eID);

private:
	CScene* m_pScene = nullptr;
	SCENE_ID m_ePreScene = SCENE_END;
	SCENE_ID m_eCurScene = SCENE_END;

private:
	void Release();
};


