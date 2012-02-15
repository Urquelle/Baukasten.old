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
		Color( u32, u32, u32, u32 );
		Color( const Color& );
		Color( Color const* );
		Color( const Colors );

		virtual ~Color();

		u32 red() const;
		u32 green() const;
		u32 blue() const;
		u32 alpha() const;
		u32 value() const;

		void rgb( u32*, u32*, u32*, u32 *a = 0 ) const;

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
		u32 mColor;
	};
} /* Baukasten */

#endif /* end of include guard: Color_H_NGT4WABN */

