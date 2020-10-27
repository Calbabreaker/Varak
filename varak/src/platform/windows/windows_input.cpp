#include <GLFW/glfw3.h>

#include "varak/core/application.h"
#include "varak/core/input.h"

namespace Varak
{
    bool Input::isKeyPressed(KeyCode key)
    {
        GLFWwindow* window = reinterpret_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        int state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(MouseCode button)
    {
        GLFWwindow* window = reinterpret_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        int state = glfwGetMouseButton(window, static_cast<int>(button));
        return state == GLFW_PRESS;
    }

    float Input::getMouseX()
    {
        GLFWwindow* window = reinterpret_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        double xPos;
        glfwGetCursorPos(window, &xPos, nullptr);
        return static_cast<float>(xPos);
    }

    float Input::getMouseY()
    {
        GLFWwindow* window = reinterpret_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        double yPos;
        glfwGetCursorPos(window, nullptr, &yPos);
        return static_cast<float>(yPos);
    }

} // namespace Varak
