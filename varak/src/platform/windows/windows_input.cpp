#include "varak/core/application.h"
#include "varak/core/input.h"

#include <GLFW/glfw3.h>

namespace Varak {

    bool Input::isKeyPressed(Key key)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        int state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(Mouse button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        int state = glfwGetMouseButton(window, static_cast<int>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {static_cast<float>(xPos), static_cast<float>(yPos)};
    }

    float Input::getMouseX()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        double xPos;
        glfwGetCursorPos(window, &xPos, nullptr);
        return static_cast<float>(xPos);
    }

    float Input::getMouseY()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(
            Application::get().getWindow().getNativeWindow());

        double yPos;
        glfwGetCursorPos(window, nullptr, &yPos);
        return static_cast<float>(yPos);
    }

} // namespace Varak
