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
	// �̳���� ���ο��� ������ �Ҹ� Ƚ�� ������, �̰� �����ָ� Leak ���� (�޸� ���� �Ҵ� �س��� ���� �����ִ°�)
	m_hBitmap = (HBITMAP)LoadImage(NULL, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (m_hBitmap == NULL)
		return E_FAIL;		// ����ó��

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
