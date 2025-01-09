#pragma once
#include "core.h"
#include <stdint.h>

typedef struct platform_window platform_window;

typedef void (*platform_window_closed_callback)(const platform_window* window);
typedef void (*platform_window_size_callback)(const platform_window* window);

ENGINE_API platform_window* platform_window_create(uint32_t width, uint32_t height,
                                                   const char* title);
ENGINE_API void platform_window_update(platform_window* window);
ENGINE_API const uint32_t platform_window_get_height(const platform_window* window);
ENGINE_API const uint32_t platform_window_get_width(const platform_window* window);
ENGINE_API void platform_window_destroy(platform_window** window);
ENGINE_API void platform_register_window_closed_callback(platform_window* window,
                                                         platform_window_closed_callback callback);
ENGINE_API void platform_register_window_size_callback(platform_window* window,
                                                       platform_window_size_callback callback);
ENGINE_API void platform_register_input_callback(platform_window* window, uint32_t key_code);
