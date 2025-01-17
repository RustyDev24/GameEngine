﻿cmake_minimum_required(VERSION 3.20)

project(GameEngine LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)


SET(PLATFORM_FILES "")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
  add_compile_definitions(ENGINE_PLATFORM_WINDOWS ENGINE_BUILD_DLL)
  message("Building for windows")
  list(APPEND PLATFORM_FILES "src/platform/windows.c")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux") 
  message("Building for linux")
  list(APPEND PLATFORM_FILES "src/platform/linux.c")
else()
  message(FATAL_ERROR "platform ${CMAKE_SYSTEM_NAME} not supported")
endif()

add_library (GameEngine SHARED "include/core.h" "include/platform.h" "include/renderer.h" "src/renderer/opengl_renderer.c" "vendor/glad/src/glad.c" ${PLATFORM_FILES})
target_link_libraries(GameEngine glfw OpenGL::GL)
