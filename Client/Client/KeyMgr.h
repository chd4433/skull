#pragma once

const DWORD KEY_UP = 0x00000001;
const DWORD KEY_DOWN = 0x00000002;
const DWORD KEY_LEFT = 0x00000004;
const DWORD KEY_RIGHT = 0x00000008;

const DWORD KEY_CHANGE = 0x00000010;
const DWORD KEY_ENTER = 0x00000020;
const DWORD KEY_DASH = 0x00000040;
const DWORD KEY_ATTACK = 0x00000080;

class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	void UpdateKey();

public:
	bool KeyDown(DWORD dwCurKey);
	bool KeyUp(DWORD dwCurKey);
	bool KeyPressing(DWORD dwCurKey);
	bool KeyCombined(DWORD dwFistKey, DWORD dwSecondKey);

private:
	DWORD m_dwCurKey = 0;
	DWORD m_dwKeyUp = 0;
	DWORD m_dwKeyDown = 0;
};

