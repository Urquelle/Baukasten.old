#ifndef NODE_H_AROBCMPN
#define NODE_H_AROBCMPN

#include "core/Color"
#include "graphics/Global"
#include "math/Vector3"

#include <GL/glew.h>
#include <GL/gl.h>

namespace Baukasten {
	class NodePrivate;

	class Node {
	public:
		Node( GLenum, const u32, const u32 );
		virtual ~Node();

		virtual void render();

		GLuint  program() const;
		void    setProgram( const GLuint );
		void    setTbo( const GLuint );
		void    setVbo( const GLuint );
		GLuint  tbo() const;
		GLuint  vbo() const;

	protected:
		virtual void prepare();
		virtual void cleanup();

		u32 dataPerVertex() const;
		u32 indexCount() const;
		GLenum type() const;
		void setType( GLenum );

		BK_IMPL_PTR( Node );
	};

	class QuadNode : public Node {
	public:
		QuadNode( GLenum, const u32, const u32 );
		virtual ~QuadNode();

		void render();

		void    setOutline( const bool );
		bool    outline() const;

	private:
		void prepare();
		void cleanup();
	};

	class LineNode : public Node {
	public:
		LineNode( GLenum, const u32, const u32 );
		virtual ~LineNode();

		void setPattern( const u16 );
		u16 pattern() const;

		void setWidth( const f32 );
		f32 width() const;

	private:
		void prepare();
		void cleanup();

		f32 m_width;
		u16 m_stipple;
	};

	class PointNode : public Node {
	public:
		PointNode( GLenum, const u32, const u32 );
		virtual ~PointNode();

		void setSize( const u32 );
		u32 size() const;

	private:
		void prepare();

		u32 m_size;
	};

	class PolyNode : public Node {
	public:
		PolyNode( GLenum, const u32, const u32 );
		virtual ~PolyNode();

		void render();

		void setOutline( const bool );
		bool outline() const;
	};

	class IFont;
	class TextNodePrivate;
	class TextNode : public Node {
	public:
		TextNode( IFont*, const string&, const Vector3&, const Color& );
		virtual ~TextNode();

		void render();

	private:
		BK_IMPL_PTR( TextNode );
	};
} /* Baukasten */

#endif /* end of include guard: NODE_H_AROBCMPN */

