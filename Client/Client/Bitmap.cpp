#include "framework.h"
#include "Bitmap.h"

CBitmap::CBitmap()
{
}

CBitmap::~CBitmap()
{
}

HRESULT CBitmap::LoadBmp(wstring strPath)
{
	HDC hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);		
	// 이놈들이 내부에서 포인터 불린 횟수 관리함, 이거 안해주면 Leak 남음 (메모리 공간 할당 해놓고 해제 안해주는거)
	m_hBitmap = (HBITMAP)LoadImage(NULL, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (m_hBitmap == NULL)
		return E_FAIL;		// 예외처리

	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	return NOERROR;
}

void CBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}

CBitmap* CBitmap::Create(wstring strPath)
{
	CBitmap* pInstance = new CBitmap;
	if (FAILED(pInstance->LoadBmp(strPath)))
		SafeDelete(pInstance);
	return pInstance;
}
