#include "StdAfx.h"
#include <Include\UtilDir.h>

CString Util::Dir::GetAppDir()
{
	TCHAR modulePath[MAX_PATH];
	::GetModuleFileNameW(NULL,modulePath,MAX_PATH);
	CStringW strPath(modulePath);
	return strPath.Left(strPath.ReverseFind(_T('\\')));
}

CString Util::Dir::GetDataDir()
{
	CString strAppDir = GetAppDir();
	return strAppDir.Left(strAppDir.ReverseFind(_T('\\'))) + _T("\\Data");
}
