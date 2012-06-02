#include "math/include/random.h"

#include <random>
#include <functional>

namespace Baukasten {

u32 Random::s_seed = 0.0;

void
Random::init( const u32 seed )
{
	s_seed = seed;
}

f32
Random::random()
{
	static uniform_real_distribution<f32> distribution( 0.0, 1.0 );
	static mt19937 engine( s_seed );
	static auto generator = bind( distribution, engine );

	return generator();
}

u32
Random::seed()
{
	return s_seed;
}

}

