#ifndef IFONT_H_1ZHU2XBV
#define IFONT_H_1ZHU2XBV

#include "core/Color"
#include "graphics/Global"
#include "math/Vector3"

namespace Baukasten {

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup graphics
	 * @{
	 *
	 * \class IFont
	 * \brief class implementing basic font management.
	 * \headerfile IFont "graphics/IFont"
	 *
	 * the class provides the interface to retrieve an object
	 * implementing the IGraphics interface.
	 */
	class BAUKASTEN_EXPORT IFont {
	public:
		/*!
		 * \brief renders the given text.
		 *
		 * render method is called by the object implementing the IGraphics
		 * interface to draw the given text.
		 *
		 * \sa IGraphics::drawText()
		 * \param text string object containing the text to be drawn.
		 * \param position vec3 struct defining the position of the text.
		 * \param color color the text will be drawn in.
		 */
		virtual void render( const string &text,
				const Vector3 &position, const Color &color ) = 0;

		/*!
		 * \brief set font size.
		 *
		 * sets the font size to the given pixel size.
		 *
		 * \param size u32 value of the wanted font size.
		 */
		virtual void setSize( const u32 size ) = 0;

		/*!
		 * \brief current font size.
		 * \return u32 current font size used.
		 */
		virtual u32 size() const = 0;

		/*!
		 * \brief set path to the font to be used.
		 * \param path path to the font that is to be used.
		 */
		virtual void setFont( const string &path ) = 0;

		/*!
		 * \brief path to the current font.
		 * \return string value representing the path.
		 */
		virtual string font() const = 0;
	};
	/** @} */
	/** @} */
} /* Baukasten  */

#endif /* end of include guard: IFONT_H_1ZHU2XBV */

