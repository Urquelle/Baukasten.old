#ifndef NODE_H_AROBCMPN
#define NODE_H_AROBCMPN

#include "model/Global"
#include "core/Math"

#include <GL/glew.h>
#include <GL/gl.h>

namespace Baukasten {
	class NodePrivate;

	class Node {
	public:
		Node( GLenum, int, int );
		virtual ~Node();

		virtual void render();

		GLuint vbo;
	protected:
		virtual void prepare();
		virtual void cleanup();

		friend class NodePrivate;
		NodePrivate* mImpl;
	};

	class QuadNode : public Node {
	public:
		QuadNode( GLenum, int, int );
		virtual ~QuadNode();

	private:
		void prepare();

		// keep some rendering flags here, which
		// might be used while rendering
	};

	class LineNode : public Node {
	public:
		LineNode( GLenum, int, int );
		virtual ~LineNode();

	private:
		void prepare();

		// keep some rendering flags here, which
		// might be used while rendering
	};

	class PointNode : public Node {
	public:
		PointNode( GLenum, int, int );
		virtual ~PointNode();

	private:
		void prepare();

		// keep some rendering flags here, which
		// might be used while rendering
	};

	class ITexture;
	class TextureNode : public Node {
	public:
		TextureNode( ITexture* );
		virtual ~TextureNode();

		void render();

		void setSize( const vec2<float>& );
		void setPosition( const vec3<float>& );

	private:
		void prepare();
		void cleanup();

		// keep some rendering flags here, which
		// might be used while rendering
		vec2<float> mSize;
		vec3<float> mPosition;
		ITexture*	mTexture;
	};
} /* Baukasten */

#endif /* end of include guard: NODE_H_AROBCMPN */

