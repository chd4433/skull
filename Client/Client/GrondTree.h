#pragma once
#include "Obj.h"
class CGrondTree : public CObj
{
public:
	enum STATE { IDLE, ATTACK, WALK,DEAD };
public:
	explicit CGrondTree();
	virtual ~CGrondTree();
public:
	// ����
	virtual HRESULT Initialize(float fStartX, float fStartY);
	virtual INT Update(const float& fTimeDelta);
	virtual VOID Render(HDC hDC);
public: 
	static CGrondTree* Create(float fStartX, float fStartY);
	HRESULT ChangeState(STATE eState);
	BOOL CheckWalk();
	BOOL CheckAttack();
	void SetRect();

private:
	STATE m_ePreState = DEAD;
	STATE m_eCurrState = DEAD;
private:
	virtual void Release();

private:
	bool m_bRight;
	RECT rectGroundTree;
};

