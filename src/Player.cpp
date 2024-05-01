#include "Player.h"

#include <iostream>

Player::Player(glm::vec3 startPos, glm::vec3 startUp, float startYaw, float startPitch)
    : position(startPos), velocity(glm::vec3(0.0f)), width(0.6f), height(1.8f),
      camera(Camera(startPos + glm::vec3(0.0f, height - 0.2f, 0.0f), startUp, startYaw, startPitch)),
      isGrounded(true), jumpHeight(1.25f) {
}

void Player::update(float deltaTime) {
    const float gravity = 13.0f;
    if (!isGrounded) {
        velocity.y -= gravity * deltaTime;
    }

    position += velocity * deltaTime;

    if (position.y < 0.0f) {
        position.y = 0.0f;
        isGrounded = true;
        velocity.y = 0.0f;
    }

    camera.Position = position + glm::vec3(0.0f, height - 0.2f, 0.0f);
    camera.updateCameraVectors();
}

void Player::processKeyboard(Movement_Direction direction, float deltaTime) {
    float vel = camera.MovementSpeed * deltaTime * 4.317f;
    glm::vec3 moveDirection = camera.Front;
    moveDirection.y = 0;
    moveDirection = glm::normalize(moveDirection);

    if (direction == FORWARD){
        position += moveDirection * vel;
    }
    if (direction == BACKWARD)
        position -= moveDirection * vel;
    if (direction == LEFT)
        position -= camera.Right * vel;
    if (direction == RIGHT)
        position += camera.Right * vel;
    if (direction == UP && isGrounded) {
        velocity.y = sqrt(2 * jumpHeight * 9.81f);
        isGrounded = false;
    }

}

void Player::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    camera.ProcessMouseMovement(xoffset, yoffset, constrainPitch);
}

void Player::processMouseScroll(float yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
