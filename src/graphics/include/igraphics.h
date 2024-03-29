#ifndef IGRAPHICS_HHQEW1LG
#define IGRAPHICS_HHQEW1LG

#include "core/Color"
#include "graphics/Global"
#include "graphics/GraphicsInterface"
#include "math/Vector"
#include "math/Vector2"
#include "math/Vector3"
#include "services/IService"

namespace Baukasten {
	class Form;
	class IFont;
	class Image;
	class Services;

	/*!
	 * \ingroup services
	 * @{
	 *
	 * \addtogroup graphics
	 * @{
	 *
	 * \class IGraphics
	 * \brief Graphics interface declaration.
	 * \headerfile IGraphics "graphics/IGraphics"
	 *
	 * declares methods that Form objects can use in order to
	 * represent the objects graphically.
	 */
	class BAUKASTEN_EXPORT IGraphics : public IService {
	public:

		/*!
		 * flags that are used with the drawInfo method.
		 */
		enum InfoFlags {
			DRAW_FPS              = 1 << 0,
			DRAW_VERSION          = 1 << 1,
			DRAW_VERSION_NAME     = 1 << 2,
			DRAW_TIME             = 1 << 3,
			DRAW_ENTITY_COUNT     = 1 << 4,
			DRAW_GRAPHICS_BACKEND = 1 << 5,
			DRAW_INPUT_BACKEND    = 1 << 6,
			DRAW_AUDIO_BACKEND    = 1 << 7,

			DRAW_ALL              = DRAW_FPS +
			                        DRAW_VERSION +
									DRAW_VERSION_NAME +
									DRAW_TIME +
									DRAW_ENTITY_COUNT +
									DRAW_GRAPHICS_BACKEND +
									DRAW_INPUT_BACKEND +
									DRAW_AUDIO_BACKEND
		};

		/*!
		 * flags that are used with createWindow method.
		 */
		enum WindowFlags {
			WINDOW = 1,
			FULLSCREEN
		};

		/*!
		 * \brief constructor
		 *
		 * receives a name of the service that implements the igraphics interface. this
		 * name can be used later to show it as info, or for other services to query
		 * the current graphics backend used if it depends on a certain backend.
		 *
		 * \param name name of the graphics service ( e. g. opengl, directx )
		 */
		IGraphics( const string &name ) : IService( name ) {}

		/*!
		 * \brief creates a window.
		 *
		 * creates a window with the given size and title.
		 *
		 * \param size size of the window.
		 * \param title window title.
		 * \param flags flags to control window parameters.
		 */
		virtual void createWindow( const Vector<u32, 2> &size, const string &title,
				WindowFlags flags = FULLSCREEN ) = 0;

		/*!
		 * \brief draws an info box on the canvas.
		 *
		 * draws a box with internal graphics/library information. the information that is
		 * shown depends on the given InfoFlags. the following information can be displayed
		 * in the current version:
		 *
		 * - Framerate
		 *
		 * - Library version
		 *
		 * - Library version name
		 *
		 * - Time
		 *
		 * - Current Amount of Model objects
		 *
		 * - Graphics backend in use
		 *
		 * - Input backend in use
		 *
		 * - Audio backend in use
		 *
		 * \param font font to be used to draw the text.
		 * \param position where the box is drawn.
		 * \param flags which info to show.
		 */
		virtual void drawInfo( IFont *font, const Vector3 &position,
				InfoFlags flags = DRAW_ALL ) = 0;

		/*!
		 * \brief draws a circle.
		 *
		 * draws a solid circle of a given radius on the given position with the given
		 * color.
		 *
		 * \param position position where the circle will be drawn.
		 * \param radius u32 value of the radius.
		 * \param color color the circle is filled with.
		 */
		virtual void drawCircle( const Vector3 &position,
				const u32 radius, const Color &color ) = 0;

		/*!
		 * \brief draws an image.
		 *
		 * the image, of which the path is given, once loaded is present to be drawn
		 * at the given position and the given size.
		 *
		 * \param path path to the image.
		 * \param size size of the image.
		 * \param position position where the image will be drawn.
		 */
		virtual void drawImage( const string &path, const Vector2 &size,
				const Vector3 &position ) = 0;

		/*!
		 * \brief draws an image.
		 *
		 * the image, that is given, is pushed into internal cache and drawn after that.
		 * the cache is in place in order to prevent loading of the image in every frame.
		 *
		 * \param image Image object.
		 * \param size size of the image.
		 * \param position position where the image will be drawn.
		 */
		virtual void drawImage( Image &image, const Vector2 &size,
				const Vector3 &position ) = 0;

		/*!
		 * \brief draws a line.
		 *
		 * draws a line with the given `from` and `to` positions. the given
		 * color is used to draw the line.
		 *
		 * the last parameter describes the pattern of the drawn line.
		 *
		 * \param from position to start the drawing.
		 * \param to position where the line stops.
		 * \param color the color of the line.
		 * \param pattern the pattern of the line.
		 */
		virtual void drawLine( const Vector3 &from, const Vector3 &to,
				const Color &color, const f32 pattern ) = 0;

		/*!
		 * \brief draws a point.
		 *
		 * draw a point on a given position and the given size and color.
		 *
		 * \param position position of the point.
		 * \param size size of the point.
		 * \param color color of the point.
		 */
		virtual void drawPoint( const Vector3 &position,
				const u32 size, const Color &color ) = 0;

		/*!
		 * \brief draws a polygon.
		 *
		 * draws a polygon with an arbitrary amount of vertices.
		 *
		 * \note no validation takes place to ensure the polygon to be convex.
		 * \param vertices a vector of vertices.
		 * \param color color to draw the polygon in.
		 * \param outline if true no filling of polygon takes place.
		 */
		virtual void drawPolygon( const vector<Vector3> &vertices,
				const Color &color, bool outline = false ) = 0;

		/*!
		 * \brief draws a rectangle.
		 *
		 * draws a rectangle with the given size at the given position.
		 *
		 * \param size size of the rectangle.
		 * \param position position where to draw the rectangle.
		 * \param color color to draw the rectangle in.
		 * \param outline if true no filling of rectangle takes place.
		 */
		virtual void drawRect( const Vector2 &size, const Vector3 &position,
				const Color &color, bool outline = false ) = 0;

		/*!
		 * \brief draws a text.
		 *
		 * draws the given string with the give font.
		 *
		 * \param font Font to be used to draw the text.
		 * \param text string to be drawn.
		 * \param position position where the text is drawn.
		 * \param color color of the drawn text.
		 */
		virtual void drawText( IFont *font, const string &text,
				const Vector3 &position, const Color &color ) = 0;

		/*!
		 * \brief current frame rate.
		 * \return f32 value representing the current frame rate.
		 */
		virtual f32 fps() const = 0;

		/*!
		 * \brief rendering routine.
		 *
		 * the main routine to draw the objects. every backend has to reimplement
		 * this function as different steps have to be made in order to render.
		 *
		 * \param form Form object that is to be drawn.
		 */
		virtual void render( Form *form ) = 0;

		/*!
		 * \brief set the window title.
		 *
		 * sets the title of the application window.
		 *
		 * \param title string containing the title.
		 */
		virtual void setWindowTitle( const string &title ) = 0;

		/*!
		 * \brief set the application window size.
		 *
		 * sets the size of the application window.
		 *
		 * \param width width of the window.
		 * \param height height of the window.
		 */
		virtual void setWindowSize( const u32 width, const u32 height ) = 0;
	};
	/** @} */
	/** @} */
}

#endif /* end of include guard: IGRAPHICS_HHQEW1LG */
