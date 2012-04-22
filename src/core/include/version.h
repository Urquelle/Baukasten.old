#ifndef VERSION_H_NWQEK9HM
#define VERSION_H_NWQEK9HM

#include "core/Global"

#include <string>

namespace Baukasten {
	using namespace std;

	/*! lib's version string */
	string version();

	/*! lib's major version */
	inline u32 major();

	/*! lib's minor version */
	inline u32 minor();

	/*! lib's patch version */
	inline u32 patch();

	/*! lib's version name */
	string name();
} /* Baukasten */

#endif /* end of include guard: VERSION_H_NWQEK9HM */

