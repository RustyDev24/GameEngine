cmake_minimum_required(VERSION 3.20)

PROJECT(Sandbox LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/GameEngine)

add_executable(Sandbox "src/main.c")

target_link_directories(GameEngine PRIVATE ${CMAKE_SOURCE_DIR}/GameEngine)
target_link_libraries(Sandbox PRIVATE GameEngine)

set(GAMEENGINE_DLL $<TARGET_FILE:GameEngine>)
set(SANDBOX_OUTPUT_DIR $<TARGET_FILE_DIR:Sandbox>)

add_custom_command(
	TARGET Sandbox POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	${GAMEENGINE_DLL}
	${SANDBOX_OUTPUT_DIR}
)