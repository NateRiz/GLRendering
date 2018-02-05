#ifndef GLRENDER_H
#define GLRENDER_H
#include <glad/glad.h>
#include <shader.h>
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class GLRender
{
public:
    GLRender(Camera*);
    ~GLRender();
    void DrawMesh();
    unsigned int AddVertex(glm::vec3 pos, glm::vec4 color);
    void AddTriangle(unsigned int, unsigned int, unsigned int);
    void ClearBuffers();

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    Shader* mShader;
    Camera* mCamera;


    static const unsigned int VERTEX_LENGTH = 7;

    std::vector<float> mVertices;
    std::vector<unsigned int> mIndices;
};

#endif // GLRENDER_H
