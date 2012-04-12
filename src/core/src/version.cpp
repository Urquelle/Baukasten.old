#include "core/include/version.h"

#include "core/Debug"

#include <sstream>

using namespace Baukasten;

#define _BK_WRAP(X) #X
#define _BK_TOSTR(X) _BK_WRAP(X)

namespace Baukasten {
	string
	version()
	{
		stringstream version;
		version << LIB_MAJOR << "." << LIB_MINOR << "." << LIB_PATCH;
		return version.str();
	}

	u32
	major()
	{
		return LIB_MAJOR;
	}

	u32
	minor()
	{
		return LIB_MINOR;
	}

	u32
	patch()
	{
		return LIB_PATCH;
	}

	string
	name()
	{
		return _BK_TOSTR( LIB_NAME );
	}
}

