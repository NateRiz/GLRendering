#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "chunk.h"
#include "glrender.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>
#include <utility>//pairs

#define Coordinate std::pair<int,int>




struct pairhash
{
public:
    template<typename T, typename U>
    std::size_t operator()(const std::pair<T,U> &value) const
    {
      return (static_cast<size_t>(value.first) << sizeof(int)*8) | value.second;
    }
};



class ChunkManager
{
public:
    ChunkManager(GLRender* render);
    ~ChunkManager();

    void Update(glm::vec3 cameraPosition, glm::vec3 cameraFront);

    static const unsigned int WORLD_SIZE = 16;// 16 x 16 Chunks


private:
    std::unordered_map<Coordinate, Chunk*, pairhash> mChunks;
    std::vector<Coordinate> mChunksLoaded;
    GLRender* mRender;
    Coordinate mCurrentChunk;
    unsigned int mNumRenderedChunks = 144; //square

    void UpdateChunksLoaded();



};

#endif // CHUNKMANAGER_H
