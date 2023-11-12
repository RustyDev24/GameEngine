PROJECT(Sandbox)

include_directories(${CMAKE_SOURCE_DIR}/GameEngine)

add_executable(Sandbox main.cpp)
target_link_libraries(Sandbox GameEngine)