#include "glad/glad.h"
#include "include/renderer.h"
#include <GLFW/glfw3.h>

// TODO: proper renderer setup -> blending and extensions etc
int renderer_init(void* window)
{
    glfwMakeContextCurrent((GLFWwindow*)window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return 0;
    }

    return 1;
}

void renderer_swap_buffers(void* window)
{
    glfwSwapBuffers((GLFWwindow*)window);
}
