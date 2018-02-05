#include "chunkmanager.h"

ChunkManager::ChunkManager(GLRender* render)
{
    mRender = render;

    mCurrentChunk = std::make_pair(0,0);
    mChunksLoaded.push_back(mCurrentChunk);
    UpdateChunksLoaded();
}

ChunkManager::~ChunkManager()
{
    std::unordered_map<Coordinate, Chunk*, pairhash>::iterator itr;

    for(itr = mChunks.begin(); itr != mChunks.end(); itr++)
    {
        delete itr->second;
    }
}


void ChunkManager::Update(glm::vec3 CameraPosition, glm::vec3 CameraFront)
{
    //std::cout<<"["<<CameraPosition[0]<<","<<CameraPosition[1]<<","<<CameraPosition[2]<<"]"<<std::endl;
    //std::cout<<"In Chunk:["<<(int)(CameraPosition[0]/16)<<","<<(int)(CameraPosition[2]/16)<<"]"<<std::endl;

    Coordinate currentChunk = std::make_pair((int)CameraPosition[0]/Chunk::CHUNK_SIZE,(int)CameraPosition[2]/Chunk::CHUNK_SIZE);
    if(currentChunk != mCurrentChunk)
    {
        mRender->ClearBuffers();
        mCurrentChunk = currentChunk;
        UpdateChunksLoaded();
    }
}

void ChunkManager::UpdateChunksLoaded()
{
    std::cout<<"Entered into Chunks:"<<mCurrentChunk.first<<","<<mCurrentChunk.second<<std::endl;
    mChunksLoaded.clear();
    mChunksLoaded.reserve(mNumRenderedChunks);

    int sideLength = (int)sqrt(mNumRenderedChunks);
    int halfSideLength = (int)sideLength/2;
    for(int i = halfSideLength - sideLength; i<sideLength - halfSideLength; i++)
    {
        for (int j = halfSideLength - sideLength; j < sideLength - halfSideLength; j++)
        {
            mChunksLoaded.push_back(std::make_pair(mCurrentChunk.first + i, mCurrentChunk.second+j));
        }
    }


    for(auto coord : mChunksLoaded)
    {
        //std::cout<<"<"<<coord.first<<","<<coord.second<<">"<<" --> ";
        Coordinate wrappedCoord = std::make_pair(coord.first % WORLD_SIZE,coord.second % WORLD_SIZE);
        //std::cout<<"<"<<wrappedCoord.first<<","<<wrappedCoord.second<<">"<<std::endl;

        if(mChunks.find(wrappedCoord) == mChunks.end())
        {
            mChunks[wrappedCoord] = new Chunk(mRender,coord);
        }
        if(mChunks[wrappedCoord]->GetWorldCoordinate() != coord)
        {
            mChunks[wrappedCoord]->SetWorldCoordinate(coord);
            std::cout<<"Test";
        }
        mChunks[wrappedCoord]->CreateMesh();
    }
}
