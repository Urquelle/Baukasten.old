#ifndef COLOUR_H_NGT4WABN
#define COLOUR_H_NGT4WABN

#include "model/Global"

namespace Baukasten {

	class BAUKASTEN_EXPORT Colour {
	public:
		enum Colours {
			BK_BLACK,	BK_WHITE,
			BK_RED	,	BK_GREEN,
			BK_BLUE,	BK_GRAY
		};

		Colour();
		Colour( uint, uint, uint, uint );
		Colour( const Colour& );
		Colour( Colour const* );
		Colour( const Colours );

		virtual ~Colour();

		uint red() const;
		uint green() const;
		uint blue() const;
		uint alpha() const;
		uint value() const;

		void rgb( uint*, uint*, uint*, uint *a = 0 ) const;

		float redF() const;
		float greenF() const;
		float blueF() const;
		float alphaF() const;

		void rgbF( float*, float*, float*, float *a = 0 ) const;

		Colour& operator=( const Colour& );

		bool operator==( const Colour& ) const;
		bool operator==( const Colours& ) const;
		bool operator!=( const Colour& ) const;
		bool operator!=( const Colours& ) const;

	private:
		uint mColor;
	};
} /* Baukasten */

#endif /* end of include guard: COLOUR_H_NGT4WABN */

