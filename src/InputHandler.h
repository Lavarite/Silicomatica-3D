#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Player.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class InputHandler {
public:
    static InputHandler* handlerInstance; // Static instance pointer

    // Constructor
    InputHandler(GLFWwindow* window, Player& player);

    // Public method to process input
    void processInput(float deltaTime);

    // Static callback functions for GLFW
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

private:
    GLFWwindow* window;
    Player& player;

    // Instance-specific methods for handling mouse and scroll input
    void instanceMouseCallback(GLFWwindow* window, double xpos, double ypos);
    void instanceScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
