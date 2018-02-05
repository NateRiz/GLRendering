#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
    Window();
    ~Window();
    GLFWwindow* GetWindow();

private:
    GLFWwindow* mWindow;
};

#endif // WINDOW_H

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
