#include "Chunk.h"
#include <vector>
#include <iostream>

Chunk::Chunk(const glm::ivec3& position, int size)
    : chunkPosition(position), size(size), VAO(0), VBO(0) {
    initializeVoxelData();
    setupMeshData();
}

Chunk::~Chunk() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Chunk::initializeVoxelData() {
    voxelData.resize(size, std::vector<int>(size, 1)); // Set all cells to 1 for a flat plane
}

void Chunk::setupMeshData() {
    vertices.clear();
    for (int x = 0; x < size; x++) {
        for (int z = 0; z < size; z++) {
            if (voxelData[x][z] == 1) {
                float fx = static_cast<float>(x), fz = static_cast<float>(z);
                float fx1 = fx + 1.0f, fz1 = fz + 1.0f;

                // Define vertices for a square (one block)
                std::vector<float> blockVertices = {
                    fx, 0.0f, fz, 0.0f, 0.0f,
                    fx1, 0.0f, fz, 1.0f, 0.0f,
                    fx1, 0.0f, fz1, 1.0f, 1.0f,
                    fx, 0.0f, fz, 0.0f, 0.0f,
                    fx1, 0.0f, fz1, 1.0f, 1.0f,
                    fx, 0.0f, fz1, 0.0f, 1.0f
                };
                vertices.insert(vertices.end(), blockVertices.begin(), blockVertices.end());
            }
        }
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Chunk::draw(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
    glBindVertexArray(0);
}
