#pragma once

typedef struct renderer renderer_t;

int renderer_init(void* window); // TODO: consider multiple windows created and destroyed
inline void renderer_swap_buffers(void* window);
