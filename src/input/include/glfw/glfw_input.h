#ifndef GLFW_INPUT_H_XWQRTCFU
#define GLFW_INPUT_H_XWQRTCFU

#include "input/Global"
#include "input/IInput"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT GlfwInput : public IInput {
	public:
		GlfwInput();
		virtual ~GlfwInput();

		void      init( CoreServices* );
		KeyState  keyState( const Key ) const;
		void      process() const;
		string    serviceName() const { return "GLFW"; }
		void      shutdown();
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_INPUT_H_XWQRTCFU */

