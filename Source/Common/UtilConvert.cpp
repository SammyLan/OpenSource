#include "StdAfx.h"
#include <Include\UtilConvert.h>
#include <memory>

CStringW Util::Convert::GBKToUnicode(CStringA const & str)
{
	int len = str.GetLength();
	std::unique_ptr<WCHAR>  szBuff ( new WCHAR[len  + 1]);
	len = ::MultiByteToWideChar(CP_THREAD_ACP,0,(LPCSTR)str,len,szBuff.get(),len+1);
	szBuff.get()[len] = L'\0';
	return CStringW(szBuff.get());
}

		
CStringA Util::Convert::UnicodeToGBK(CStringW const & str)
{
	int len = str.GetLength();
	std::unique_ptr<CHAR> szBuff ( new CHAR[len * 2  + 1]);
	BOOL bUsedDef = FALSE;
	len = ::WideCharToMultiByte(CP_THREAD_ACP,0,(LPCWSTR)str,len,szBuff.get(),len * 2+1,NULL,&bUsedDef);
	szBuff.get()[len] = L'\0';
	return CStringA(szBuff.get());
}