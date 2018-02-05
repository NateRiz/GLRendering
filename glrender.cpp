#include "glrender.h"

GLRender::GLRender(Camera* camera)
{
    mCamera = camera;
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);


}

GLRender::~GLRender()
{

}




void GLRender::DrawMesh()
{
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
