#ifndef NODE_H_AROBCMPN
#define NODE_H_AROBCMPN

#include "core/Color"
#include "core/Math"
#include "core/Color"
#include "graphics/Global"

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

		BK_PIMPL_PTR( Node );
	};

	class QuadNode : public Node {
	public:
		QuadNode( GLenum, const u32, const u32 );
		virtual ~QuadNode();

		void render();

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

		void setWidth( const float );
		float width() const;

	private:
		void prepare();
		void cleanup();

		float m_width;
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

	class IFont;
	class TextNodePrivate;
	class TextNode : public Node {
	public:
		TextNode( IFont*, const string&, const vec3<float>&, const Color& );
		virtual ~TextNode();

		void render();

	private:
		BK_PIMPL_PTR( TextNode );
	};
} /* Baukasten */

#endif /* end of include guard: NODE_H_AROBCMPN */

