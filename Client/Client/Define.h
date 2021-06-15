#pragma once

#define WINCX 800
#define WINCY 600


// Singleton
#define NO_COPY(ClassName)														\
private:																\
	ClassName(const ClassName& Obj);			\
	ClassName& operator=(const ClassName& Obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if(nullptr == m_pInstance)			\
		{									\
			m_pInstance = new ClassName;	\
		}									\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName*	m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;

#define MAX_VKEY 0xff

#define OBJ_NOEVENT 0
#define OBJ_DEAD 1

#define  PLAYERATT 50
#define  PLAYERATTCLOSE 100
#define MONSTERDISTANCEATT 10
#define  MONSTERCLOSEATT 30

extern HWND g_hWnd;

// ±ÍÂ÷´ÏÁò
class CObj;
typedef list<CObj*>					OBJLIST;
typedef OBJLIST::iterator			OBJITER;
