#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "Camera.h"


enum Movement_Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP
};

class Player {
public:
    glm::vec3 position; // Player's position in the world
    glm::vec3 velocity; // Player's current velocity
    float width;
    float height;
    Camera camera; // Camera object that represents the player's view
    bool isGrounded; // Flag to check if the player is on the ground
    float jumpHeight; // Height that the player can jump

    Player(glm::vec3 startPos, glm::vec3 startUp, float startYaw, float startPitch);
    void update(float deltaTime);
    void processKeyboard(Movement_Direction direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
};

#endif // PLAYER_H
