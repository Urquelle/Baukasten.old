#ifndef RANDOM_H_BLZLJCAW
#define RANDOM_H_BLZLJCAW

#include "math/Global"

namespace Baukasten {
	/*!
	 * \brief Random class declaration.
	 */
	class Random {
	public:
		static f32 random();

		static void init( const u32 );
		static u32 seed();

	private:
		static u32 s_seed;
	};
} /* Baukasten */

#endif /* end of include guard: RANDOM_H_BLZLJCAW */

