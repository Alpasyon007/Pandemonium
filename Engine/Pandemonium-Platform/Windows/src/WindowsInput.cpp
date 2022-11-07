#include "ppch.h"
#include "WindowsInput.h"

#include "Application.h"
#include <glfw/glfw3.h>

namespace Pandemonium {

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int			state  = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int			state  = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double		xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return {static_cast<float>(xPos), static_cast<float>(yPos)};
	}

	float WindowsInput::GetMosueXImpl() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double		xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return static_cast<float>(xPos);
	}

	float WindowsInput::GetMosueYImpl() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double		xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return static_cast<float>(yPos);
	}

} // namespace Pandemonium