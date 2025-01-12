#include "GLFW/glfw3.h"
#include "include/platform.h"
#include <include/renderer.h>
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
    platform_input_callback keyboard_input_callback;
    platform_mouse_move_callback mouse_position_callback;
    platform_mouse_button_callback mouse_button_callback;
    platform_mouse_wheel_callback mouse_wheel_callback;
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

    if (pl_window && pl_window->window_size_callback)
    {
        pl_window->window_size_callback(pl_window);
    }
}

static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);

    if (pl_window && pl_window->keyboard_input_callback)
    {
        pl_window->keyboard_input_callback(key, action);
    }
}

static void glfw_mouse_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);
    if (pl_window && pl_window->mouse_position_callback)
    {
        pl_window->mouse_position_callback(xpos, ypos);
    }
}

static void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);
    if (pl_window && pl_window->mouse_button_callback)
    {
        pl_window->mouse_button_callback(button, action);
    }
}

static void glfw_mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    platform_window* pl_window = (platform_window*)glfwGetWindowUserPointer(window);

    if (pl_window && pl_window->mouse_wheel_callback)
    {
        pl_window->mouse_wheel_callback(yoffset);
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

    window->window_size_callback = NULL;
    window->window_closed_callback = NULL;

    glfwSetWindowUserPointer(window->window, window);

    // NOTE: this is not final
    glfwSetWindowCloseCallback(window->window, glfw_window_close_callback);
    glfwSetWindowSizeCallback(window->window, glfw_window_size_callback);
    glfwSetKeyCallback(window->window, glfw_key_callback);
    glfwSetMouseButtonCallback(window->window, glfw_mouse_button_callback);
    glfwSetCursorPosCallback(window->window, glfw_mouse_pos_callback);
    glfwSetScrollCallback(window->window, glfw_mouse_scroll_callback);

    renderer_init(window->window);
    return window;
}

void platform_window_update(platform_window* window)
{
    renderer_swap_buffers(window->window);
    glfwPollEvents();
}

// NOTE: make it someway so that all windows get the same callback by default
// NOTE: Currently only the current window gets callback
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

void platform_register_input_callback(platform_window* window, platform_input_callback callback)
{
    window->keyboard_input_callback = callback;
}

void platform_register_mouse_move_callback(platform_window* window,
                                           platform_mouse_move_callback callback)
{
    window->mouse_position_callback = callback;
}

void platform_register_mouse_button_callback(platform_window* window,
                                             platform_mouse_button_callback callback)
{
    window->mouse_button_callback = callback;
}

void platform_register_mouse_scroll_callback(platform_window* window,
                                             platform_mouse_wheel_callback callback)
{
    window->mouse_wheel_callback = callback;
}

const uint32_t platform_window_get_height(const platform_window* window)
{
    return window->height;
}

const uint32_t platform_window_get_width(const platform_window* window)
{
    return window->width;
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
