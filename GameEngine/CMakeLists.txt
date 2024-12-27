cmake_minimum_required(VERSION 3.20)

project(GameEngine LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_compile_definitions(ENGINE_PLATFORM_WINDOWS ENGINE_BUILD_DLL)

SET(PLATFORM_FILES "")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message("Building for windows")
  list(APPEND PLATFORM_FILES "src/platform/windows.c")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux") 
  message("Building for linux")
  message(FATAL_ERROR "linux not implemented yet")
else()
  message(FATAL_ERROR "platform ${CMAKE_SYSTEM_NAME} not supported")
endif()

add_library (GameEngine SHARED "include/core.h" "include/platform.h" ${PLATFORM_FILES})
target_link_libraries(GameEngine glfw OpenGL::GL)