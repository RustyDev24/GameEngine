// #include "include/platform.h"
#include "GLFW/glfw3.h"
#include "include/platform.h"
#include "include/renderer.h"
#include <stdlib.h>

static int s_windows = 0;

typedef struct platform_window
{
    GLFWwindow* window;
    uint32_t width;
    uint32_t height;
    const char* title;

    platform_window_closed_callback window_closed_callback;
    platform_window_size_callback window_size_callback;
} platform_window;

static void glfw_window_close_callback(GLFWwindow* window)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);
    if (pl_window && pl_window->window_closed_callback)
    {
        pl_window->window_closed_callback(pl_window);
    }
}

static void glfw_window_size_callback(GLFWwindow* window, int width, int height)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);
    pl_window->height = height;
    pl_window->width = width;

    if (pl_window && pl_window->window_closed_callback)
    {
        pl_window->window_size_callback(pl_window);
    }
}

platform_window* platform_window_create(uint32_t width, uint32_t height, const char* title)
{
    if (s_windows == 0)
    {
        glfwInit();
    }

    platform_window* window = (platform_window*)malloc(sizeof(platform_window));
    window->window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
    window->width = width;
    window->height = height;
    window->title = title;

    glfwSetWindowUserPointer(window->window, window);

    glfwSetWindowCloseCallback(window->window, glfw_window_close_callback);

    renderer_init(window->window);

    return window;
}

void platform_window_update(platform_window* window)
{
    renderer_swap_buffers(window->window);
    glfwPollEvents();
}

const uint32_t platform_window_get_height(const platform_window* window)
{
    return window->height;
}

const uint32_t platform_window_get_width(const platform_window* window)
{
    return window->width;
}

void platform_register_window_closed_callback(platform_window* window,
                                              platform_window_closed_callback callback)
{
    window->window_closed_callback = callback;
}

void platform_register_window_size_callback(platform_window* window,
                                            platform_window_size_callback callback)
{
    window->window_size_callback = callback;
}

void platform_window_destroy(platform_window** window)
{
    if (!window || !(*window))
        return;

    platform_window* win = *window;
    glfwDestroyWindow(win->window);
    if (--s_windows == 0)
    {
        glfwTerminate();
    }

    free(win);
    *window = NULL;
}
