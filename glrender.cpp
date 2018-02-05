#include "glrender.h"

GLRender::GLRender(Camera* camera)
{
    mCamera = camera;
    mShader = new Shader("/home/nathan/Documents/CPPFiles/LLV2/shader.vert","/home/nathan/Documents/CPPFiles/LLV2/shader.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glGenVertexArrays(1,&mLightVAO);
    glGenBuffers(1,&mLightVBO);
    glBindVertexArray(mLightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mLightVBO);




    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


}

GLRender::~GLRender()
{
    delete mShader;
}

unsigned int GLRender::AddVertex(glm::vec3 pos, glm::vec4 color)
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

void GLRender::AddTriangle(unsigned int i1, unsigned int i2, unsigned int i3)
{
    mIndices.push_back(i1);
    mIndices.push_back(i2);
    mIndices.push_back(i3);
}

void GLRender::ClearBuffers()
{
    mIndices.clear();
    mVertices.clear();
}


void GLRender::DrawMesh()
{

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

    mShader->use();

    glm::mat4 projection = glm::perspective(glm::radians(mCamera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    mShader->setMat4("projection", projection);
    glm::mat4 view = mCamera->GetViewMatrix();
    mShader->setMat4("view", view);
    glm::mat4 model(1.0f);
    mShader->setMat4("model",model);
    glm::vec3 light(1.0f,1.0f,1.0f);
    mShader->setVec3("lightColor",light);



    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size()* sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float)*3));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT,0);

}
