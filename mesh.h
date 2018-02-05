#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

class Mesh
{
public:
    Mesh();

    unsigned int AddVertex(glm::vec3 pos, glm::vec4 color);
    void AddTriangle(unsigned int, unsigned int, unsigned int);


private:

    unsigned int mVAO;
    unsigned int mVBO;
    unsigned int mEBO;
    Shader* mShader;

    std::vector<float> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif // MESH_H
