#ifndef GLFW_INPUT_H_XWQRTCFU
#define GLFW_INPUT_H_XWQRTCFU

#include "global.h"

#include "iinput.h"

namespace Baukasten {
	class CoreServices;

	class BAUKASTEN_EXPORT GlfwInput : public IInput {
	public:
		GlfwInput();
		virtual ~GlfwInput();

		bool init( CoreServices* );
		void process() const;
		void shutdown();
		string getServiceName() const { return "GLFW"; }
	};
} /* Baukasten */

#endif /* end of include guard: GLFW_INPUT_H_XWQRTCFU */

