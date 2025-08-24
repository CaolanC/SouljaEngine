cmake_minimum_required(VERSION 3.28.3)
project(Soulja C)

set(SDL_VIDEO            ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_X11        ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_WAYLAND    ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL     ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL_GLX ON  CACHE BOOL "" FORCE)
set(SDL_VIDEO_OPENGL_EGL ON  CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)

add_subdirectory(thirdpartypoopers/libhv)
add_subdirectory(thirdpartypoopers/libsdl-org)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")

add_library(SouljaLib ${SRC_FILES})

add_executable(Soulja apps/soulja_server/main.c)
add_executable(SouljaClient apps/soulja_client/main.c)

target_include_directories(SouljaLib PRIVATE internal)

target_include_directories(Soulja PRIVATE internal)



set_target_properties(Soulja PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(SouljaClient PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_link_libraries(Soulja PRIVATE SouljaLib hv)
target_link_libraries(SouljaClient PRIVATE SDL3::SDL3 OpenGL::GL)
