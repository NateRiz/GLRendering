#include "chunk.h"

Chunk::Chunk(GLRender* render, std::pair<int,int> worldCoordinate)
{
    mRender = render;
    mWorldCoordinate = worldCoordinate;
}

Chunk::~Chunk()
{

}

std::pair<int,int> Chunk::GetWorldCoordinate()
{
    return mWorldCoordinate;
}
void Chunk::SetWorldCoordinate(std::pair<int,int> worldCoordinate)
{
    //Dynamic coordinates have to wrap.
    mWorldCoordinate = worldCoordinate;
}


void Chunk::CreateMesh()
{

    noise::module::Perlin myModule;
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(myModule);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(CHUNK_SIZE,CHUNK_SIZE);
    heightMapBuilder.SetBounds(mWorldCoordinate.first*.25,
                               mWorldCoordinate.first*.25 + .25,
                               mWorldCoordinate.second*.25,
                               mWorldCoordinate.second*.25 + .25);

    heightMapBuilder.Build();

    /* //WRITE TO FILE
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.Render();

    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("m_<" + std::to_string(mWorldCoordinate.first)+","\
                           + std::to_string(mWorldCoordinate.second)+">");
    writer.WriteDestFile();
    */

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                int xPos = x + (CHUNK_SIZE * mWorldCoordinate.first);
                int zPos = z + (CHUNK_SIZE * mWorldCoordinate.second);
                int yPos = CHUNK_SIZE * heightMap.GetValue(x, z);
                CreateCube(xPos,yPos,zPos);
            }
    }

}


void Chunk::CreateCube(int x, int y, int z)
{
    glm::vec3 p1(x+Block::BLOCK_SIZE,y+Block::BLOCK_SIZE,z+Block::BLOCK_SIZE);
    glm::vec3 p2(x+Block::BLOCK_SIZE,y+Block::BLOCK_SIZE,z-Block::BLOCK_SIZE);
    glm::vec3 p3(x+Block::BLOCK_SIZE,y-Block::BLOCK_SIZE,z+Block::BLOCK_SIZE);
    glm::vec3 p4(x+Block::BLOCK_SIZE,y-Block::BLOCK_SIZE,z-Block::BLOCK_SIZE);
    glm::vec3 p5(x-Block::BLOCK_SIZE,y+Block::BLOCK_SIZE,z+Block::BLOCK_SIZE);
    glm::vec3 p6(x-Block::BLOCK_SIZE,y+Block::BLOCK_SIZE,z-Block::BLOCK_SIZE);
    glm::vec3 p7(x-Block::BLOCK_SIZE,y-Block::BLOCK_SIZE,z+Block::BLOCK_SIZE);
    glm::vec3 p8(x-Block::BLOCK_SIZE,y-Block::BLOCK_SIZE,z-Block::BLOCK_SIZE);

    unsigned int i1, i2, i3, i4, i5, i6, i7, i8;

    const glm::vec4 RGBA(0.2f, 0.6f, 0.2f, 1.0f);//green
    //Front
    i1 = mRender->AddVertex(p7,RGBA);//bl
    i2 = mRender->AddVertex(p5,RGBA);//tl
    i3 = mRender->AddVertex(p3,RGBA);//br
    i4 = mRender->AddVertex(p1,RGBA);//tr

    mRender->AddTriangle(i1, i2, i3);
    mRender->AddTriangle(i2, i3, i4);

    //Right
    i3 = mRender->AddVertex(p3,RGBA);//bl
    i4 = mRender->AddVertex(p1,RGBA);//tl
    i5 = mRender->AddVertex(p4,RGBA);//br
    i6 = mRender->AddVertex(p2,RGBA);//tr

    mRender->AddTriangle(i3, i4, i5);
    mRender->AddTriangle(i4, i5, i6);

    //Left
    i1 = mRender->AddVertex(p7,RGBA);//br
    i2 = mRender->AddVertex(p5,RGBA);//tr
    i7 = mRender->AddVertex(p8,RGBA);//bl
    i8 = mRender->AddVertex(p6,RGBA);//tl

    mRender->AddTriangle(i1, i2, i7);
    mRender->AddTriangle(i2, i7, i8);

    //Back
    i5 = mRender->AddVertex(p4,RGBA);//bl
    i6 = mRender->AddVertex(p2,RGBA);//tl
    i7 = mRender->AddVertex(p8,RGBA);//br
    i8 = mRender->AddVertex(p6,RGBA);//tr

    mRender->AddTriangle(i5, i6, i7);
    mRender->AddTriangle(i6, i7, i8);

    //Top
    i2 = mRender->AddVertex(p5,RGBA);//bl
    i4 = mRender->AddVertex(p1,RGBA);//br
    i8 = mRender->AddVertex(p6,RGBA);//tr
    i6 = mRender->AddVertex(p2,RGBA);//tl


    mRender->AddTriangle(i2, i4, i8);
    mRender->AddTriangle(i4, i8, i6);

    //Bottom
    i1 = mRender->AddVertex(p7,RGBA);//tl
    i3 = mRender->AddVertex(p3,RGBA);//tr
    i7 = mRender->AddVertex(p8,RGBA);//bl
    i5 = mRender->AddVertex(p4,RGBA);//br

    mRender->AddTriangle(i1, i3, i7);
    mRender->AddTriangle(i3, i7, i5);
}
