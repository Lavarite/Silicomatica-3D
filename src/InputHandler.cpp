#include "InputHandler.h"

InputHandler* InputHandler::handlerInstance = nullptr;

InputHandler::InputHandler(GLFWwindow* window, Player& player) : window(window), player(player) {
    handlerInstance = this;
}

void InputHandler::processInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.processKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        player.processKeyboard(UP, deltaTime);
}

void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (handlerInstance) {
        handlerInstance->instanceMouseCallback(window, xpos, ypos);
    }
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (handlerInstance) {
        handlerInstance->instanceScrollCallback(window, xoffset, yoffset);
    }
}

// Instance-specific methods for handling callbacks
void InputHandler::instanceMouseCallback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = SCR_WIDTH / 2.0f;
    static float lastY = SCR_HEIGHT / 2.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    player.processMouseMovement(xoffset, yoffset);
}

void InputHandler::instanceScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    player.processMouseScroll(yoffset);
}