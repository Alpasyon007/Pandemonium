#include "ppch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace Pandemonium {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) { ASSERT(windowHandle, "Window handle is null!"); }

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASSERT(status, "Could not initalize GLAD!");

		LOG_INFO("OpenGL Info:");
		LOG_INFO("OpenGL Vendor: %s", glGetString(GL_VENDOR));
		LOG_INFO("OpenGL Renderer: %s", glGetString(GL_RENDERER));
		LOG_INFO("OpenGL Version: %s", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }
} // namespace Pandemonium