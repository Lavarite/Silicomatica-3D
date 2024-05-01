#include "WorldManager.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <glm/ext/matrix_transform.hpp>

WorldManager::WorldManager(int chunkSize, int viewDistance)
    : chunkSize(chunkSize), viewDistance(viewDistance) {}

WorldManager::~WorldManager() {}

glm::ivec3 WorldManager::worldToChunkCoords(const glm::vec3& position) {
    int x = static_cast<int>(floor(position.x / chunkSize));
    int y = static_cast<int>(floor(position.y / chunkSize));
    int z = static_cast<int>(floor(position.z / chunkSize));
    return glm::ivec3(x, y, z);
}

void WorldManager::updatePlayerPosition(const glm::vec3& position) {
    glm::ivec3 chunkCoord = worldToChunkCoords(position);
    if (chunkCoord != currentPlayerChunk) {
        currentPlayerChunk = chunkCoord;
        ensureChunksLoaded(chunkCoord);
    }
}

void WorldManager::ensureChunksLoaded(const glm::ivec3& currentChunk) {
    std::unordered_set<glm::ivec3, KeyFuncs> chunksToLoad;
    std::unordered_set<glm::ivec3, KeyFuncs> chunksToUnload;

    for (int x = -viewDistance; x <= viewDistance; x++) {
        for (int z = -viewDistance; z <= viewDistance; z++) {
            glm::ivec3 offset(x, 0, z);
            glm::ivec3 loadCoord = currentChunk + offset;
            chunksToLoad.insert(loadCoord);
        }
    }

    // Determine which chunks to unload
    for (auto& pair : chunks) {
        if (chunksToLoad.find(pair.first) == chunksToLoad.end()) {
            chunksToUnload.insert(pair.first);
        }
    }

    // Load new chunks
    for (auto& chunkCoord : chunksToLoad) {
        if (chunks.find(chunkCoord) == chunks.end()) {
            loadChunk(chunkCoord);
        }
    }

    // Unload far-away chunks
    for (auto& chunkCoord : chunksToUnload) {
        unloadChunk(chunkCoord);
    }
}

void WorldManager::loadChunk(const glm::ivec3& chunkCoord) {
    if (chunks.find(chunkCoord) == chunks.end()) {
        std::cout << "Loading chunk at: " << chunkCoord.x << ", " << chunkCoord.y << ", " << chunkCoord.z << std::endl;
        chunks[chunkCoord] = std::make_unique<Chunk>(chunkCoord * chunkSize, chunkSize);
    }
}

void WorldManager::unloadChunk(const glm::ivec3& chunkCoord) {
    if (chunks.find(chunkCoord) != chunks.end()) {
        std::cout << "Unloading chunk at: " << chunkCoord.x << ", " << chunkCoord.y << ", " << chunkCoord.z << std::endl;
        chunks.erase(chunkCoord); // Remove the chunk from the map
    }
}

void WorldManager::renderWorld(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    std::vector<ChunkRenderInfo> sortedChunks;

    for (auto& pair : chunks) {
        float distance = glm::distance(glm::vec3(pair.first * chunkSize), glm::vec3(0.0f)); // Use chunk center
        sortedChunks.push_back({pair.first, distance, pair.second.get()});
    }

    std::sort(sortedChunks.begin(), sortedChunks.end(), [](const ChunkRenderInfo& a, const ChunkRenderInfo& b) {
        return a.distance < b.distance;
    });

    shader.use();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    for (const auto& info : sortedChunks) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(info.position * chunkSize));
        shader.setMat4("model", model);
        info.chunkPtr->draw(shader);
    }
}
