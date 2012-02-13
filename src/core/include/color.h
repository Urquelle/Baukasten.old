#ifndef Color_H_NGT4WABN
#define Color_H_NGT4WABN

#include "model/Global"

namespace Baukasten {

	class BAUKASTEN_EXPORT Color {
	public:
		enum Colors {
			BK_BLACK,	BK_WHITE,
			BK_RED	,	BK_GREEN,
			BK_BLUE,	BK_GRAY
		};

		Color();
		Color( uint, uint, uint, uint );
		Color( const Color& );
		Color( Color const* );
		Color( const Colors );

		virtual ~Color();

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

		Color& operator=( const Color& );

		bool operator==( const Color& ) const;
		bool operator==( const Colors& ) const;
		bool operator!=( const Color& ) const;
		bool operator!=( const Colors& ) const;

	private:
		uint mColor;
	};
} /* Baukasten */

#endif /* end of include guard: Color_H_NGT4WABN */

