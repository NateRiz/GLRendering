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

    void ClearBuffers();

private:
    Camera* mCamera;
};

#endif // GLRENDER_H
