#pragma once
#include <stdint.h>

typedef struct platform_window platform_window;

platform_window* platform_create_window(uint32_t width, uint32_t height, const char* title);
int platform_get_window_closed_state(platform_window* window);
void platform_update_window(platform_window* window);
void platform_destroy_window(platform_window** window);