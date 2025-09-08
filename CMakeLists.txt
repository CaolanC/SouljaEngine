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
add_subdirectory(thirdpartypoopers/cglm)
add_subdirectory(thirdpartypoopers/glad)
add_subdirectory(thirdpartypoopers/FastNoiseLite)

file(GLOB_RECURSE SRC_FILES "${CMAKE_SOURCE_DIR}/src/server/*.c")
file(GLOB_RECURSE CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/src/client/*.c")
file(GLOB_RECURSE SHARED_SRC_FILES "${CMAKE_SOURCE_DIR}/src/shared/*.c")

add_library(SouljaLib ${SRC_FILES})
add_library(SouljaClientLib ${CLIENT_SRC_FILES})
add_library(SouljaSharedLib ${SHARED_SRC_FILES})

add_executable(Soulja apps/soulja_server/main.c)
add_executable(SouljaClient apps/soulja_client/main.c)

target_include_directories(SouljaLib PRIVATE internal)
target_include_directories(SouljaClientLib PRIVATE internal)
target_include_directories(SouljaSharedLib PRIVATE internal)

target_include_directories(SouljaClient PRIVATE internal)
target_include_directories(Soulja PRIVATE internal)

set_target_properties(Soulja PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
set_target_properties(SouljaClient PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_link_libraries(SouljaSharedLib PRIVATE fastnoiselitelib)
target_link_libraries(Soulja PRIVATE SouljaSharedLib SouljaLib hv)
target_link_libraries(SouljaClient PRIVATE SouljaSharedLib SouljaClientLib SDL3::SDL3 OpenGL::GL cglm m glad fastnoiselitelib)
