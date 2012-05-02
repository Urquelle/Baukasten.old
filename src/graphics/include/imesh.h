#ifndef IMESH_H_TAVBJYU2
#define IMESH_H_TAVBJYU2

#include "core/Color"
#include "graphics/Global"
#include "math/Vector3"
#include "math/Vector2"

namespace Baukasten {
	/*!
	 * \brief IMesh class declaration.
	 */
	class BAUKASTEN_EXPORT IMesh {
	public:
		enum Type {
			COLOR,
			LINE,
			POINT,
			POLYGON,
			QUAD,
			TRIANGLE
		};

		enum Attribute {
			PATTERN,
			SIZE,
			WIDTH
		};

		static IMesh& createMesh( const Type, const f32*, const u32 );
		static IMesh& createLine( const Vector3&, const Vector3&, const f32 );
		static IMesh& createPoint( const Vector3&, const u32);
		static IMesh& createRect( const Vector3&, const Vector2& );
		static IMesh& createPolygon( const f32*, const u32 );

		virtual u32   indexCount() const = 0;
		virtual bool  isWireframe() const = 0;
		virtual void  render() = 0;
		virtual void  set( Attribute, const u32 ) = 0;
		virtual void  set( Attribute, const f32 ) = 0;
		virtual void  setData( const f32*, const u32, const u32 ) = 0;
		virtual void  setWireframe( bool ) = 0;
	    virtual Type  type() const = 0;
		virtual u32   vertexCount() const = 0;

	protected:
		virtual void prepare();
		virtual void cleanup();
	};
} /* Baukasten */

#endif /* end of include guard: IMESH_H_TAVBJYU2 */

