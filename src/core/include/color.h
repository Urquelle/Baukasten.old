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
		Color( int32, int32, int32, int32 );
		Color( const Color& );
		Color( Color const* );
		Color( const Colors );

		virtual ~Color();

		int32 red() const;
		int32 green() const;
		int32 blue() const;
		int32 alpha() const;
		int32 value() const;

		void rgb( int32*, int32*, int32*, int32 *a = 0 ) const;

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
		int32 mColor;
	};
} /* Baukasten */

#endif /* end of include guard: Color_H_NGT4WABN */

