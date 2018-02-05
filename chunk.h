#ifndef CHUNK_H
#define CHUNK_H

#include "glrender.h"
#include "block.h"
#include "noise/noise.h"
#include "noiseutils.h"
#include <utility>
#include <string>



class Chunk
{
public:
    Chunk(GLRender*, std::pair<int,int> worldCoordinate);
    ~Chunk();
    void CreateMesh();
    std::pair<int,int> GetWorldCoordinate();
    void SetWorldCoordinate(std::pair<int,int>);



    static const int CHUNK_SIZE = 16;

private:

    Block** mBlocks;
    GLRender* mRender;
    std::pair<int,int> mWorldCoordinate;

    void CreateCube(int, int, int);

};

#endif // CHUNK_H
