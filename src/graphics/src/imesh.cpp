#include "graphics/include/imesh.h"
#include "graphics/MeshImpl"

namespace Baukasten {

IMesh&
IMesh::createMesh( const Type type, const f32 *data,
		const u32 vertexCount )
{
	return Mesh::createMesh( type, data, vertexCount );
}

IMesh&
IMesh::createLine( const Vector3 &from, const Vector3 &to,
		const f32 width )
{
	return Mesh::createLine( from, to, width );
}

IMesh&
IMesh::createPoint( const Vector3 &pos, const u32 size )
{
	return Mesh::createPoint( pos, size );
}

IMesh&
IMesh::createRect( const Vector3 &pos, const Vector2 &size )
{
	return Mesh::createRect( pos, size );
}

IMesh&
IMesh::createPolygon( const f32 *data, const u32 count )
{
	return Mesh::createPolygon( data, count );
}

void
IMesh::prepare()
{
}

void
IMesh::cleanup()
{
}

}
