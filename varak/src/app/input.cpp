#include "varak/app/input.h"
#include "varak/app/application.h"

#include <GLFW/glfw3.h>

namespace Varak {

    bool Input::isKeyPressed(KeyCode key)
    {
        GLFWwindow* window = Application::get().getWindow().getHandle();

        int state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(MouseCode button)
    {
        GLFWwindow* window = Application::get().getWindow().getHandle();

        int state = glfwGetMouseButton(window, static_cast<int>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::getMousePosition()
    {
        GLFWwindow* window = Application::get().getWindow().getHandle();

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float Input::getMouseX()
    {
        GLFWwindow* window = Application::get().getWindow().getHandle();

        double xPos;
        glfwGetCursorPos(window, &xPos, nullptr);
        return static_cast<float>(xPos);
    }

    float Input::getMouseY()
    {
        GLFWwindow* window = Application::get().getWindow().getHandle();

        double yPos;
        glfwGetCursorPos(window, nullptr, &yPos);
        return static_cast<float>(yPos);
    }

} // namespace Varak
