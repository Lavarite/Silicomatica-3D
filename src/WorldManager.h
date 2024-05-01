#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <unordered_map>
#include <memory>
#include <glm/glm.hpp>
#include "Chunk.h"
#include "Shader.h"

struct KeyFuncs {
    size_t operator()(const glm::ivec3& k) const {
        return std::hash<int>()(k.x) ^ (std::hash<int>()(k.y) << 1) ^ (std::hash<int>()(k.z) << 2);
    }

    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

class WorldManager {
public:
    WorldManager(int chunkSize, int viewDistance);
    ~WorldManager();

    void updatePlayerPosition(const glm::vec3& position);
    void renderWorld(Shader& shader, const glm::mat4& view, const glm::mat4& projection);

private:
    struct ChunkRenderInfo {
        glm::ivec3 position;
        float distance;
        Chunk* chunkPtr;
    };

    std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, KeyFuncs> chunks;
    int chunkSize;
    int viewDistance;
    glm::ivec3 currentPlayerChunk;

    glm::ivec3 worldToChunkCoords(const glm::vec3& position);
    void loadChunk(const glm::ivec3& chunkCoord);
    void unloadChunk(const glm::ivec3& chunkCoord);
    void ensureChunksLoaded(const glm::ivec3& currentChunk);
};

#endif
