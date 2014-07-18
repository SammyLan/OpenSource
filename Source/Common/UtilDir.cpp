#include "StdAfx.h"
#include <Include\UtilDir.h>

CStringW Util::Dir::GetAppDirW()
{
	WCHAR modulePath[MAX_PATH];
	::GetModuleFileNameW(NULL,modulePath,MAX_PATH);
	CStringW strPath(modulePath);
	return strPath.Left(strPath.ReverseFind(L'\\'));
}

CStringA Util::Dir::GetAppDirA()
{
	CHAR modulePath[MAX_PATH];
	::GetModuleFileNameA(NULL,modulePath,MAX_PATH);
	CStringA strPath(modulePath);
	return strPath.Left(strPath.ReverseFind('\\'));
}