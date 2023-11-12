# CMakeList.txt : CMake project for GameEngineDevelopment, include source and define
# project specific logic here.
#

# Add source to this project's executable.
project(GameEngine)

add_compile_definitions(ENGINE_PLATFORM_WINDOWS ENGINE_BUILD_DLL)
add_library (GameEngine SHARED "application.cpp" "application.h" "core.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GameEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
