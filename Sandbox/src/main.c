#include "include/platform.h"
#include <stdio.h>

static int is_running = 1;

void stop_app(const platform_window* window)
{
    is_running = 0;
}

void resize(const platform_window* window)
{
    printf("window resized\nNEW SIZE: H(%d) W(%d)\n", platform_window_get_height(window),
           platform_window_get_width(window));
}

int main()
{
    platform_window* window = platform_window_create(720, 480, "Hello C");
    platform_register_window_closed_callback(window, stop_app);
    // platform_register_window_size_callback(window, resize);

    while (is_running)
    {
        platform_window_update(window);
    }

    platform_window_destroy(&window);
    return 0;
}
