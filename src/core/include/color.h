#ifndef Color_H_NGT4WABN
#define Color_H_NGT4WABN

#include "core/Global"

namespace Baukasten {

	/*!
	 * \brief color class.
	 * \ingroup core
	 * \headerfile Color "core/Color"
	 *
	 * provides basic functionality to deal with rgb(a) color.
	 */
	class BAUKASTEN_EXPORT Color {
	public:

		/*!
		 * \brief predefined colors
		 */
		enum Colors {
			BK_BLACK,	BK_WHITE,
			BK_RED	,	BK_GREEN,
			BK_BLUE,	BK_GRAY
		};

		/*! constructor */
		Color();

		/*!
		 * \brief constructor
		 *
		 * \param r value for the red part of the color.
		 * \param g value for the green part of the color.
		 * \param b value for the blue part of the color.
		 * \param a value for the alpha value.
		 */
		Color( const u32, const u32, const u32, const u32 );

		/*!
		 * \brief copy constructor
		 * \param other reference to a Color object.
		 */
		Color( const Color& );

		/*!
		 * \brief copy constructor
		 * \param other const pointer to a Color object.
		 */
		Color( Color const* );

		/*!
		 * \brief constructor that accepts predefined color.
		 * \param value Colors value.
		 */
		Color( const Colors );

		/*! destructor */
		virtual ~Color();

		/*!
		 * \brief getter for the red part of the color.
		 * \return u32 value.
		 */
		u32 red() const;

		/*!
		 * \brief getter for the green part of the color.
		 * \return u32 value.
		 */
		u32 green() const;

		/*!
		 * \brief getter for the blue part of the color.
		 * \return u32 value.
		 */
		u32 blue() const;

		/*!
		 * \brief getter for the alpha.
		 * \return u32 value.
		 */
		u32 alpha() const;

		/*!
		 * \brief color as an int value
		 *
		 * returns u32 value that represents the color value. the value
		 * is divided in the following sections:
		 *
		 * - 0xXX000000 alpha
		 *
		 * - 0x00XX0000 red
		 *
		 * - 0x0000XX00 green
		 *
		 * - 0x000000XX blue
		 *
		 * \return u32 value representing the color.
		 */
		u32 value() const;

		/*!
		 * \brief sets the given pointer.
		 *
		 * sets the value of the given pointer to their according color
		 * parts.
		 *
		 * \param r pointer for the red part of the color.
		 * \param g pointer for the green part of the color.
		 * \param b pointer for the blue part of the color.
		 * \param a pointer for alpha.
		 */
		void rgb( u32*, u32*, u32*, u32 *a = 0 ) const;

		/*!
		 * \brief getter for the red part of the color.
		 * \return f32 value.
		 */
		f32 redF() const;

		/*!
		 * \brief getter for the green part of the color.
		 * \return f32 value.
		 */
		f32 greenF() const;

		/*!
		 * \brief getter for the blue part of the color.
		 * \return f32 value.
		 */
		f32 blueF() const;

		/*!
		 * \brief getter for alpha.
		 * \return f32 value.
		 */
		f32 alphaF() const;

		/*!
		 * \brief sets the given pointer.
		 *
		 * sets the value of the given pointer to their according color
		 * parts.
		 *
		 * \param r pointer for the red part of the color.
		 * \param g pointer for the green part of the color.
		 * \param b pointer for the blue part of the color.
		 * \param a pointer for alpha.
		 */
		void rgbF( f32*, f32*, f32*, f32 *a = 0 ) const;

		/*!
		 * \brief assignment operator
		 * \param other Color object to copy the values from.
		 * \return reference to Color object.
		 */
		Color& operator=( const Color& );

		/*!
		 * \brief compares the given color with the object's value.
		 * \return true if all components of the two colors are the same, false otherwise.
		 */
		bool operator==( const Color& ) const;

		/*!
		 * \brief compares the given predefined color with the object's value.
		 * \return true if all components of the two colors are the same,
		 * false otherwise.
		 */
		bool operator==( const Colors& ) const;

		/*!
		 * \brief compares the given color with the object's value.
		 * \return true if at least one component of the two colors are the
		 * different, false otherwise.
		 */
		bool operator!=( const Color& ) const;

		/*!
		 * \brief compares the given predefined color with the object's value.
		 * \return true if at least one component of the two colors are the
		 * different, false otherwise.
		 */
		bool operator!=( const Colors& ) const;

	private:
		u32 m_color;
	};
} /* Baukasten */

#endif /* end of include guard: Color_H_NGT4WABN */

