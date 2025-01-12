#pragma once
#include "core.h"
#include <stdint.h>

// NOTE: maybe have a platform_state which set's callbacks for all windows
typedef struct platform_window platform_window;

typedef void (*platform_window_closed_callback)(const platform_window* window);
typedef void (*platform_window_size_callback)(const platform_window* window);
typedef void (*platform_input_callback)(int32_t key, int32_t action);
typedef void (*platform_mouse_move_callback)(double xpos, double ypos);
typedef void (*platform_mouse_button_callback)(int32_t button, int32_t action);
typedef void (*platform_mouse_wheel_callback)(
    double delta); // NOTE: currently takes the scroll offset maybe make it (-1, 1) ?

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
ENGINE_API void platform_register_input_callback(platform_window* window,
                                                 platform_input_callback callback);

ENGINE_API void platform_register_mouse_move_callback(platform_window* window,
                                                      platform_mouse_move_callback callback);

ENGINE_API void platform_register_mouse_button_callback(platform_window* window,
                                                        platform_mouse_button_callback callback);

ENGINE_API void platform_register_mouse_scroll_callback(platform_window* window,
                                                        platform_mouse_wheel_callback callback);
