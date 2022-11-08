#ifndef OPEN_GL_CONTEXT_H
#define OPEN_GL_CONTEXT_H

#include "GraphicsContext.h"

struct GLFWwindow;

namespace Pandemonium {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

} // namespace Pandemonium

#endif /* OPEN_GL_CONTEXT_H */