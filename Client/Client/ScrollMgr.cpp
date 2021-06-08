#include "framework.h"
#include "ScrollMgr.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CScrollManager)

int CScrollManager::m_iScrollX = 0;
int CScrollManager::m_iScrollY = 0;
CScrollManager::CScrollManager()
{
}


CScrollManager::~CScrollManager()
{
}
void CScrollManager::ScrollLock(SCENE_ID eID)
{

	if (m_iScrollX > 0)
		m_iScrollX = 0;
	if (m_iScrollY > 0)
		m_iScrollY = 0;
	switch (eID)
	{
	case SCENE_LOGO:
		break;
	case SCENE_TUTORIAL:
		if (WINCX - 1600 > m_iScrollX)
			m_iScrollX = WINCX - 1600;
		if (WINCY - 600 > m_iScrollY)
			m_iScrollY = WINCY - 600;
		break;
	case SCENE_STAGE1:
		if (WINCX - 2400 > m_iScrollX)
			m_iScrollX = WINCX - 2400;
		if (WINCY - 600 > m_iScrollY)
			m_iScrollY = WINCY - 600;
		break;
	case SCENE_STAGE2:
		break;
	case SCENE_GAMEOVER:
		break;
	case SCENE_END:
		break;
	default:
		break;
	}


}
