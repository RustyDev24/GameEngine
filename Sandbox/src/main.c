#include <stdio.h>

#include "include/platform.h"

int main()
{
    platform_window* window = platform_create_window(720, 480, "Hello C");
    int running = 1;

    while (running)
    {
        int state = platform_get_window_closed_state(window);

        if (state == 1)
            running = 0;
        if (state == -1)
        {
            printf("invalid window\n");
            return 1;
        }

        platform_update_window(window);
    }

    platform_destroy_window(&window);
    return 0;
}