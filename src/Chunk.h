#ifndef CHUNK_H
#define CHUNK_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shader.h"

class Chunk {
public:
    Chunk(const glm::ivec3& position, int size);
    ~Chunk();

    void draw(Shader& shader);

private:
    glm::ivec3 chunkPosition;
    int size; // Size of the chunk (e.g., 16)
    std::vector<float> vertices;
    unsigned int VAO, VBO;

    static const int height = 1; // Flat plane height
    std::vector<std::vector<int>> voxelData; // 2D vector for voxel data

    void initializeVoxelData();
    void setupMeshData();
};

#endif
