#include "mesh.h"

Mesh::Mesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    mShader = new Shader("/home/nathan/Documents/CPPFiles/LLV2/shader.vert","/home/nathan/Documents/CPPFiles/LLV2/shader.frag");
}
Mesh::~Mesh()
{
    delete mShader;
}

void Mesh::AddTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
    mIndices.push_back(i1);
    mIndices.push_back(i2);
    mIndices.push_back(i3);
}

void Mesh::ClearBuffers()
{
    mIndices.clear();
    mVertices.clear();
}
unsigned int Mesh::AddVertex(glm::vec3 pos, glm::vec4 color)
{
    mVertices.push_back(pos.x);
    mVertices.push_back(pos.y);
    mVertices.push_back(pos.z);
    mVertices.push_back(color.x);
    mVertices.push_back(color.y);
    mVertices.push_back(color.z);
    mVertices.push_back(color.w);
    return mVertices.size()/VERTEX_LENGTH - 1;
}
void Mesh::Draw()
{
    glm::mat4 projection = glm::perspective(glm::radians(mCamera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    mShader->setMat4("projection", projection);
    glm::mat4 view = mCamera->GetViewMatrix();
    mShader->setMat4("view", view);
    glm::mat4 model(1.0f);
    mShader->setMat4("model",model);
    glm::vec3 light(1.0f,1.0f,1.0f);
    mShader->setVec3("lightColor",light);
}
