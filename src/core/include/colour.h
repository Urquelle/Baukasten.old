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

		inline int getR() const { return mR; }
		inline int getG() const { return mG; }
		inline int getB() const { return mB; }
		inline int getAlpha() const { return mAlpha; }

	private:
		int mR;
		int mG;
		int mB;
		int mAlpha;
	};
} /* Baukasten */

#endif /* end of include guard: COLOUR_H_NGT4WABN */

