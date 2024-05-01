#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Player.h"
#include "InputHandler.h"
#include "WorldManager.h" // Include WorldManager
#include <iostream>

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Callback functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // GLFW: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Voxel Game", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    Shader ourShader("../assets/shaders/vertexShader.glsl", "../assets/shaders/fragmentShader.glsl");

    // Player and Input Handling
    Player player(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);
    InputHandler inputHandler(window, player);

    // Set callbacks for mouse and scroll
    glfwSetCursorPosCallback(window, inputHandler.mouse_callback);
    glfwSetScrollCallback(window, inputHandler.scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize WorldManager with a chunk size of 16 and a view distance of 4
    const int chunkSize = 16;
    const int viewDistance = 4;
    WorldManager worldManager(chunkSize, viewDistance);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input handling
        inputHandler.processInput(deltaTime);
        player.update(deltaTime);
        worldManager.updatePlayerPosition(player.camera.Position);

        // Calculate projection and view matrices
        glm::mat4 projection = glm::perspective(glm::radians(player.camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = player.camera.GetViewMatrix();

        // Rendering commands
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Drawing the voxel chunks through WorldManager
        worldManager.renderWorld(ourShader, view, projection);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose
    glfwTerminate();
    return 0;
}
