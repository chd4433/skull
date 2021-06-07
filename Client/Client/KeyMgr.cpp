#include "framework.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)

CKeyMgr::CKeyMgr()
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::UpdateKey()
{
	m_dwCurKey = 0;

	for (int i = 0; i < MAX_VKEY; ++i)
	{
		if (m_dwCurKey && !(GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
		if (!m_dwCurKey && (GetAsyncKeyState(i) & 0x8000))
			m_dwCurKey = !m_dwCurKey;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwCurKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwCurKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwCurKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_CHANGE;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_ENTER;
	if (GetAsyncKeyState(0x5A) & 0x8000)		// 0x5A == 'Z'
		m_dwCurKey |= KEY_DASH;
}

bool CKeyMgr::KeyDown(DWORD dwCurKey)
{
	// ���� ������ ���� ���� ������ �� true
	if (!(m_dwKeyDown & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	// m_dwKeyDown�� ����
	// ���� ������ �ְ� ���� ������ �ʾ��� ��
	else if ((m_dwKeyDown & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyUp(DWORD dwCurKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� true
	if ((m_dwKeyUp & dwCurKey) && !(m_dwCurKey & dwCurKey))
	{
		// m_dwKeyUp�� ����
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	// ���� ������ ���� ���� ������ �� 
	else if (!(m_dwKeyUp & dwCurKey) && (m_dwCurKey & dwCurKey))
	{
		m_dwKeyUp |= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyMgr::KeyPressing(DWORD dwCurKey)
{
	if (m_dwCurKey & dwCurKey)
		return true;

	return false;
}

// ex) Ctrl + V
bool CKeyMgr::KeyCombined(DWORD dwFistKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && KeyPressing(dwFistKey))
		return true;

	return false;
}