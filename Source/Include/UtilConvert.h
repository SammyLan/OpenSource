#pragma once
#include <Include\CommonExp.h>
namespace Util
{
	namespace Convert
	{
		COMMON_API CStringW GBKToUnicode(CStringA const & str);
		COMMON_API CStringA UnicodeToGBK(CStringW const & str);
	}
}