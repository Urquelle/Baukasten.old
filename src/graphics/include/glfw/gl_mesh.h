#ifndef GL_MESH_H_C7N2NRKX
#define GL_MESH_H_C7N2NRKX

#include "graphics/Global"
#include "graphics/IMesh"

namespace Baukasten {

	class GlMeshPrivate;

	/*!
	 * \brief GlMesh class declaration.
	 */
	class GlMesh : public IMesh {
	public:

		static GlMesh& createMesh( const Type, const f32*, const u32 );
		static GlMesh& createLine( const Vector3&, const Vector3&, const f32 );
		static GlMesh& createPoint( const Vector3&, const u32 );
		static GlMesh& createRect( const Vector3&, const Vector2& );
		static GlMesh& createPolygon( const f32*, const u32 );

		u32           indexCount() const;
		bool          isWireframe() const;
		void          set( Attribute, const u32 );
		void          set( Attribute, const f32 );
		void          setData( const f32*, const u32, const u32 );
		void          setWireframe( bool );
		Type          type() const;
		u32           vertexCount() const;
		virtual void  render();

		virtual ~GlMesh();

	protected:
		virtual void prepare();
		virtual void cleanup();

	private:
		GlMesh();
		GlMesh( const GlMesh& );

		BK_IMPL_PTR( GlMesh );
	};
} /* Baukasten */

#endif /* end of include guard: GL_MESH_H_C7N2NRKX */

