#include "framework.h"
#include "BitmapMgr.h"
#include "Bitmap.h"

IMPLEMENT_SINGLETON(CBitmapMgr)

CBitmapMgr::CBitmapMgr()
{

}

CBitmapMgr::~CBitmapMgr()
{
	Release();
}

HDC CBitmapMgr::FindBmp(wstring strKey)
{
	auto iter = m_mapBmp.find(strKey);

	if (m_mapBmp.end() == iter)
		return nullptr;

	return iter->second->GetMemDC();
}

HRESULT CBitmapMgr::LoadBmp(wstring strKey, wstring strPath)
{
	auto iter = m_mapBmp.find(strKey); //이름똑같은거있냐?
	if (iter == m_mapBmp.end())	// 없냐?
	{
		CBitmap* pBitmap = CBitmap::Create(strPath);
		if (pBitmap == nullptr)
			return E_FAIL;	//예외처리
		m_mapBmp.emplace(strKey, pBitmap);
	}
	return NOERROR;
}

HRESULT CBitmapMgr::LoadBmpFromPath(wstring strPath)
{
	//std::locale::global(std::locale("Korean"));
#ifdef _UNICODE
	wifstream fin;
#else
	wifstream fin;
#endif // _UNICODE

	fin.open(strPath);

	if (fin.fail())
		return E_FAIL;;

	wstring strImageKey = L"";
	wstring strImagePath = L"";

	while (true)
	{
		if (fin.eof())
			break;

		fin >> strImageKey >> strImagePath;

		if (FAILED(LoadBmp(strImageKey, strImagePath)))
			return E_FAIL;
	}

	fin.close();

	return NOERROR;
}

BOOL CBitmapMgr::CheckBmp(wstring strKey)
{
	auto iter = m_mapBmp.find(strKey);

	if (iter == m_mapBmp.end())
		return FALSE;

	return TRUE;
}

VOID CBitmapMgr::Release()
{
	for (auto& iter : m_mapBmp)
		SafeDelete(iter.second);
	m_mapBmp.clear();
}
