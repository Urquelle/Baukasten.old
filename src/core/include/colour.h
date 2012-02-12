#ifndef COLOUR_H_NGT4WABN
#define COLOUR_H_NGT4WABN

#include "model/Global"

namespace Baukasten {

	class BAUKASTEN_EXPORT Colour {
	public:
		Colour();
		Colour( int, int, int, int );

		virtual ~Colour();

		inline int red() const { return mR; }
		inline int green() const { return mG; }
		inline int blue() const { return mB; }
		inline int alpha() const { return mA; }

		void rgb( int*, int*, int*, int *a = 0 ) const;

		inline float redF() const { return red() / 255.0; }
		inline float greenF() const { return green() / 255.0; }
		inline float blueF() const { return blue() / 255.0; }
		inline float alphaF() const { return alpha() / 255.0; }

		void rgbF( float*, float*, float*, float *a = 0 ) const;

	private:
		int mR, mG, mB, mA;
	};
} /* Baukasten */

#endif /* end of include guard: COLOUR_H_NGT4WABN */

