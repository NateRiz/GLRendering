#include <window.h>
#include <glrender.h>
#include <camera.h>
#include "chunkmanager.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

void ProcessInput(GLFWwindow *window);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
float lastX = 800/2.f;
float lastY = 600/2.f;

Camera camera;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


int main()
{

    Window window;
    glfwSetCursorPosCallback(window.GetWindow(), MouseCallback);

    GLRender render(&camera);


    ChunkManager chunkManager(&render);




    while (!glfwWindowShouldClose(window.GetWindow()))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        ProcessInput(window.GetWindow());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);







        render.DrawMesh();

        chunkManager.Update(camera.Position, camera.Front);

        auto x = glGetError();
        if(x != 0)
        {
            std::cout<<"ERROR:"<<x<<std::endl;
            throw std::invalid_argument("");
        }

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }



    return 0;

}

void ProcessInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{


    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}



