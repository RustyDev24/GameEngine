// #include "include/platform.h"
#include "GLFW/glfw3.h"
#include <stdlib.h>

static int s_windows = 0;

typedef struct platform_window 
{
	GLFWwindow* window;
	uint32_t width;
	uint32_t height;
	const char* title;
} platform_window;

platform_window* platform_create_window(uint32_t width, uint32_t height, const char* title) 
{
	if (s_windows == 0) 
	{
		glfwInit();
	}

	platform_window* window = (platform_window*) malloc(sizeof(platform_window));
	window->window = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
	window->width  = width;
	window->height = height;
	window->title  = title;

	glfwMakeContextCurrent(window->window);

	return window;
}

int platform_get_window_closed_state(platform_window* window) 
{
	if (window == NULL) return -1;

	return glfwWindowShouldClose(window->window);
}

void platform_update_window(platform_window* window) 
{
	glfwSwapBuffers(window->window);
	glfwPollEvents();
}

void platform_destroy_window(platform_window** window) {
	if (!window || !(*window)) return;

	platform_window* win = *window;
	glfwDestroyWindow(win->window);
	if (--s_windows == 0) {
		glfwTerminate();
	}

	free(win);
	*window = NULL;
}