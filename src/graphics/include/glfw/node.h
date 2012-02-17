#ifndef NODE_H_AROBCMPN
#define NODE_H_AROBCMPN

#include "core/Math"
#include "graphics/Global"

#include <GL/glew.h>
#include <GL/gl.h>

namespace Baukasten {
	class NodePrivate;
	class GlTexture;

	class Node {
	public:
		Node( GLenum, const u32, const u32 );
		virtual ~Node();

		virtual void render();

		void addTexture( GlTexture* );

		GLuint vbo;
	protected:
		virtual void prepare();
		virtual void cleanup();

		BK_PIMPL_PTR( Node );
	};

	class QuadNode : public Node {
	public:
		QuadNode( GLenum, const u32, const u32 );
		virtual ~QuadNode();

	private:
		void prepare();

		// keep some rendering flags here, which
		// might be used while rendering
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

		float mWidth;
		u16 mStipple;
	};

	class PointNode : public Node {
	public:
		PointNode( GLenum, const u32, const u32 );
		virtual ~PointNode();

		void setSize( const u32 );
		u32 size() const;

	private:
		void prepare();

		u32 mSize;
	};
} /* Baukasten */

#endif /* end of include guard: NODE_H_AROBCMPN */

