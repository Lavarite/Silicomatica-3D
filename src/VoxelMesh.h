#ifndef VOXELMESH_H
#define VOXELMESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class VoxelMesh {
public:
    VoxelMesh();
    ~VoxelMesh();
    void draw(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
    void addVoxel(int x, int y, int z);
    void removeVoxel(int x, int y, int z);
    void setupMesh();
    void createFlatTerrain(int height);

private:
    unsigned int VBO, VAO;
    static const int WORLD_SIZE = 16;
    int voxelData[WORLD_SIZE][WORLD_SIZE][WORLD_SIZE];
};

#endif
