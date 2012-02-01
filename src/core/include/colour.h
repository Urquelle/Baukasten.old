#ifndef COLOUR_H_NGT4WABN
#define COLOUR_H_NGT4WABN

namespace Baukasten
{
	class Colour
	{
	public:
		Colour();
		Colour( int, int, int, int );

		virtual ~Colour();

		inline int getRed() const { return mR; }
		inline int getGreen() const { return mG; }
		inline int getBlue() const { return mB; }
		inline int getAlpha() const { return mA; }

		void getRgb( int*, int*, int*, int *a = 0 ) const;

		inline float getRedF() const { return getRed() / 256.0; }
		inline float getGreenF() const { return getGreen() / 256.0; }
		inline float getBlueF() const { return getBlue() / 256.0; }
		inline float getAlphaF() const { return getAlpha() / 256.0; }

		void getRgbF( float*, float*, float*, float *a = 0 ) const;

	private:
		int mR;
		int mG;
		int mB;
		int mA;
	};
} /* Baukasten */

#endif /* end of include guard: COLOUR_H_NGT4WABN */

