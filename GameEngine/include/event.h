#pragma once
#include "core.h"

typedef struct event_register event_register;

ENGINE_API int event_initialize();
ENGINE_API int event_shutdown();
ENGINE_API int event_fire();
